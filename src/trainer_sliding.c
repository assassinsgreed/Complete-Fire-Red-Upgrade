#include "defines.h"
#include "defines_battle.h"
#include "../include/string_util.h"

#include "../include/new/battle_util.h"
#include "../include/new/mega.h"
#include "../include/new/multi.h"
#include "../include/new/trainer_sliding.h"
#include "../include/new/trainer_sliding_data.h"

#include "../include/constants/songs.h"
#include "../include/constants/trainer_classes.h"
/*
trainer_sliding.c
	handles mid-battle trainer sliding and related message.
*/

struct TrainerSlide
{
	u16 trainerId;
	const u8* msgFirstDown;
	const u8* msgLastSwitchIn;
	const u8* msgLastLowHp;
};

struct DynamaxTrainerSlide
{
	u16 trainerId;
	const u8* dynamaxMsg;
};

static const struct TrainerSlide sTrainerSlides[] =
{
	// Format {Trainer hex index, msg on first faint, msg on last switch in, msg on last pkmn low hp}
	{0x1, NULL, sText_Rival1_LastSwitchIn, sText_Rival1_LowHP}, // First rival battle
	{0xE, NULL /*sText_Leader1_FirstMonDown*/, sText_Leader1_LastSwitchIn, sText_Leader1_LowHP}, // Gym Leader Terrence
	{0x1C, NULL, sText_Rival2_LastSwitchIn, sText_Rival2_LowHP}, // Second rival battle
	{0x23, NULL, sText_Irene_LastSwitchIn, sText_Irene_LowHP}, // Pluto Admin Irene (double battle)
	{0x40, sText_Leader2_FirstMonDown, sText_Leader2_LastSwitchIn, sText_Leader2_LowHP}, // Gym Leader Stella
	{0x69, sText_Leader3_FirstMonDown, sText_Leader3_LastSwitchIn, sText_Leader3_LowHP}, // Gym Leader Raine
	{0x88, sText_Rival3_FirstMonDown, sText_Rival3_LastSwitchIn, sText_Rival3_LowHP}, // Third rival battle
	{0x9A, sText_Leader4_FirstMonDown, sText_Leader4_LastSwitchIn, sText_Leader4_LowHP}, // Gym Leader Chance
	{0x9B, NULL, sText_Casey1_LastSwitchIn, sText_Casey1_LowHP}, // Female Casey battle 1
	{0x9C, NULL, sText_Casey1_LastSwitchIn, sText_Casey1_LowHP}, // Male Casey battle 1
	{0xAE, NULL, sText_Casey2_LastSwitchIn, sText_Casey2_LowHP}, // Female Casey battle 2
	{0xAF, NULL, sText_Casey2_LastSwitchIn, sText_Casey2_LowHP}, // Female Casey battle 2
	{0xC8, sText_Ronald_FirstMonDown, sText_Ronald_LastSwitchIn, sText_Ronald_LowHP}, // Pluto Admin Ronald
	{0xC9, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Vaporeon
	{0xCA, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Jolteon
	{0xCB, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Flareon
	{0xCC, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Espeon
	{0xCD, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Umbreon
	{0xCE, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Leafeon
	{0xCF, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Glaceon
	{0xD0, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Sylveon
	{0xE9, sText_Leader5F_FirstMonDown, sText_Leader5F_LastSwitchIn, sText_Leader5F_LowHP}, // Gym Leader Casey (F)
	{0xEA, sText_Leader5M_FirstMonDown, sText_Leader5M_LastSwitchIn, sText_Leader5M_LowHP}, // Gym Leader Casey (M)
	{0x10A, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Vaporeon
	{0x10B, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Jolteon
	{0x10C, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Flareon
	{0x10D, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Espeon
	{0x10E, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Umbreon
	{0x10F, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Leafeon
	{0x110, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Glaceon
	{0x111, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Sylveon
	{0x117, sText_Leader6_FirstMonDown, sText_Leader6_LastSwitchIn, sText_Leader6_LowHP}, // Gym Leader Abby
	{0x137, sText_Irene_PlutoHQ_FirstMonDown, sText_Irene_PlutoHQ_LastSwitchIn, sText_Irene_PlutoHQ_LowHP}, // Pluto Admin Irene (Pluto HQ)
	{0x138, sText_Ronald_PlutoHQ_FirstMonDown, sText_Ronald_PlutoHQ_LastSwitchIn, sText_Ronald_PlutoHQ_LowHP}, // Pluto Admin Ronald (Pluto HQ)
	{0x139, sText_Kurtis_FirstMonDown, sText_Kurtis_LastSwitchIn, sText_Kurtis_LowHP}, // Pluto Leader Kurtis
	{0x16D, sText_EmraldinRivalEvent_FirstMonDown, sText_EmraldinRivalEvent_LastSwitchIn, sText_EmraldinRivalEvent_LowHP}, // Rival event in Emraldin Quay
	{0x1A9, sText_DeveloperCollin_FirstMonDown, sText_DeveloperCollin_LastSwitchIn, sText_DeveloperCollin_LowHP}, // Developer Collin 1
	{0x1AA, sText_DeveloperCollin_FirstMonDown, sText_DeveloperCollin_LastSwitchIn, sText_DeveloperCollin_LowHP}, // Developer Collin 2
	{0x1AB, sText_DeveloperCrystal_FirstMonDown, sText_DeveloperCrystal_LastSwitchIn, sText_DeveloperCrystal_LowHP}, // Developer Crystal 1
	{0x1AC, sText_DeveloperCrystal_FirstMonDown, sText_DeveloperCrystal_LastSwitchIn, sText_DeveloperCrystal_LowHP}, // Developer Crystal 2
	{0x1AD, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Noam
	{0x1AE, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Ashley
	{0x1AF, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Chelsea
	{0x1B0, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Buddy
	{0x1B1, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Gawain
	{0x1B2, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Skylar
	{0x1B3, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Bella
	{0x1B4, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Flash
	{0x1B5, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Terra
	{0x1B6, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Seifa
	{0x1B7, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Rocco
	{0x1B8, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Janice
	{0x1B9, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Antoinette
	{0x1BA, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Ryu
	{0x1BB, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Caspar
	{0x1BC, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Darcy
	{0x1BD, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Mason
	{0x1BE, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Faye
	{0x1C5, sText_Leader7_FirstMonDown, sText_Leader7_LastSwitchIn, sText_Leader7_LowHP}, // Gym Leader Iris
	{0x1D5, sText_Rival6_FirstMonDown, sText_Rival6_LastSwitchIn, sText_Rival6_LowHP}, // Carnelidge Volcano Rival
	{0x1D6, sText_Alistair_FirstMonDown, sText_Alistair_LastSwitchIn, sText_Alistair_LowHP}, // Carnelidge Volcano Alistair
	{0x1E5, sText_Leader8_FirstMonDown, sText_Leader8_LastSwitchIn, sText_Leader8_LowHP}, // Gym Leaders Dennis and Dee
	{0x1FF, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Seventh rival battle, Vaporeon
	{0x200, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Seventh rival battle, Jolteon
	{0x201, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Seventh rival battle, Flareon
	{0x202, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Seventh rival battle, Espeon
	{0x203, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Seventh rival battle, Umbreon
	{0x204, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Seventh rival battle, Leafeon
	{0x205, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Seventh rival battle, Glaceon
	{0x206, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Seventh rival battle, Sylveon
	{0x207, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Rival exhibition battle (secondary team)
	{0x208, sText_Hannah_FirstMonDown, sText_Hannah_LastSwitchIn, sText_Hannah_LowHP}, // Elite Four Hannah
	{0x209, sText_Lucas_FirstMonDown, sText_Lucas_LastSwitchIn, sText_Lucas_LowHP}, // Elite Four Lucas
	{0x20A, sText_Jenna_FirstMonDown, sText_Jenna_LastSwitchIn, sText_Jenna_LowHP}, // Elite Four Jenna
	{0x20B, sText_Thomas_FirstMonDown, sText_Thomas_LastSwitchIn, sText_Thomas_LowHP}, // Elite Four Thomas
	{0x20C, sText_Champion_FirstMonDown, sText_Champion_LastSwitchIn, sText_Champion_LowHP}, // Champion Selene
	{0x20D, sText_AlistairPostCredits_FirstMonDown, sText_AlistairPostCredits_LastSwitchIn, sText_AlistairPostCredits_LowHP}, // Post-Credits Alistair battle
	{526, sText_Leader1Rematch_FirstMonDown, sText_Leader1Rematch_LastSwitchIn, sText_Leader1Rematch_LowHp}, // Gym Leader Terrence Rematch
	{527, sText_Leader1Rematch_FirstMonDown, sText_Leader1Rematch_LastSwitchIn, sText_Leader1Rematch_LowHp}, // Gym Leader Terrence Rematch
	{528, sText_Leader1Rematch_FirstMonDown, sText_Leader1Rematch_LastSwitchIn, sText_Leader1Rematch_LowHp}, // Gym Leader Terrence Rematch
	{529, sText_Leader1Rematch_FirstMonDown, sText_Leader1Rematch_LastSwitchIn, sText_Leader1Rematch_LowHp}, // Gym Leader Terrence Rematch
	{530, sText_Leader2Rematch_FirstMonDown, sText_Leader2Rematch_LastSwitchIn, sText_Leader2Rematch_LowHp}, // Gym Leader Stella Rematch
	{531, sText_Leader2Rematch_FirstMonDown, sText_Leader2Rematch_LastSwitchIn, sText_Leader2Rematch_LowHp}, // Gym Leader Stella Rematch
	{532, sText_Leader2Rematch_FirstMonDown, sText_Leader2Rematch_LastSwitchIn, sText_Leader2Rematch_LowHp}, // Gym Leader Stella Rematch
	{533, sText_Leader2Rematch_FirstMonDown, sText_Leader2Rematch_LastSwitchIn, sText_Leader2Rematch_LowHp}, // Gym Leader Stella Rematch
	{534, sText_Leader3Rematch_FirstMonDown, sText_Leader3Rematch_LastSwitchIn, sText_Leader3Rematch_LowHp}, // Gym Leader Raine Rematch
	{535, sText_Leader3Rematch_FirstMonDown, sText_Leader3Rematch_LastSwitchIn, sText_Leader3Rematch_LowHp}, // Gym Leader Raine Rematch
	{536, sText_Leader3Rematch_FirstMonDown, sText_Leader3Rematch_LastSwitchIn, sText_Leader3Rematch_LowHp}, // Gym Leader Raine Rematch
	{537, sText_Leader3Rematch_FirstMonDown, sText_Leader3Rematch_LastSwitchIn, sText_Leader3Rematch_LowHp}, // Gym Leader Raine Rematch
	{538, sText_Leader4Rematch_FirstMonDown, sText_Leader4Rematch_LastSwitchIn, sText_Leader4Rematch_LowHp}, // Gym Leader Chance Rematch
	{539, sText_Leader4Rematch_FirstMonDown, sText_Leader4Rematch_LastSwitchIn, sText_Leader4Rematch_LowHp}, // Gym Leader Chance Rematch
	{540, sText_Leader4Rematch_FirstMonDown, sText_Leader4Rematch_LastSwitchIn, sText_Leader4Rematch_LowHp}, // Gym Leader Chance Rematch
	{541, sText_Leader4Rematch_FirstMonDown, sText_Leader4Rematch_LastSwitchIn, sText_Leader4Rematch_LowHp}, // Gym Leader Chance Rematch
	{542, sText_Leader5FRematch_FirstMonDown, sText_Leader5FRematch_LastSwitchIn, sText_Leader5FRematch_LowHp}, // Gym Leader Casey (Female) Rematch
	{543, sText_Leader5FRematch_FirstMonDown, sText_Leader5FRematch_LastSwitchIn, sText_Leader5FRematch_LowHp}, // Gym Leader Casey (Female) Rematch
	{544, sText_Leader5FRematch_FirstMonDown, sText_Leader5FRematch_LastSwitchIn, sText_Leader5FRematch_LowHp}, // Gym Leader Casey (Female) Rematch
	{545, sText_Leader5FRematch_FirstMonDown, sText_Leader5FRematch_LastSwitchIn, sText_Leader5FRematch_LowHp}, // Gym Leader Casey (Female) Rematch
	{546, sText_Leader5MRematch_FirstMonDown, sText_Leader5MRematch_LastSwitchIn, sText_Leader5MRematch_LowHp}, // Gym Leader Casey (Male) Rematch
	{547, sText_Leader5MRematch_FirstMonDown, sText_Leader5MRematch_LastSwitchIn, sText_Leader5MRematch_LowHp}, // Gym Leader Casey (Male) Rematch
	{548, sText_Leader5MRematch_FirstMonDown, sText_Leader5MRematch_LastSwitchIn, sText_Leader5MRematch_LowHp}, // Gym Leader Casey (Male) Rematch
	{549, sText_Leader5MRematch_FirstMonDown, sText_Leader5MRematch_LastSwitchIn, sText_Leader5MRematch_LowHp}, // Gym Leader Casey (Male) Rematch
	{550, sText_Leader6Rematch_FirstMonDown, sText_Leader6Rematch_LastSwitchIn, sText_Leader6Rematch_LowHp}, // Gym Leader Abby Rematch
	{551, sText_Leader6Rematch_FirstMonDown, sText_Leader6Rematch_LastSwitchIn, sText_Leader6Rematch_LowHp}, // Gym Leader Abby Rematch
	{552, sText_Leader6Rematch_FirstMonDown, sText_Leader6Rematch_LastSwitchIn, sText_Leader6Rematch_LowHp}, // Gym Leader Abby Rematch
	{553, sText_Leader6Rematch_FirstMonDown, sText_Leader6Rematch_LastSwitchIn, sText_Leader6Rematch_LowHp}, // Gym Leader Abby Rematch
	{554, sText_Leader7Rematch_FirstMonDown, sText_Leader7Rematch_LastSwitchIn, sText_Leader7Rematch_LowHp}, // Gym Leader Iris Rematch
	{555, sText_Leader7Rematch_FirstMonDown, sText_Leader7Rematch_LastSwitchIn, sText_Leader7Rematch_LowHp}, // Gym Leader Iris Rematch
	{556, sText_Leader7Rematch_FirstMonDown, sText_Leader7Rematch_LastSwitchIn, sText_Leader7Rematch_LowHp}, // Gym Leader Iris Rematch
	{557, sText_Leader7Rematch_FirstMonDown, sText_Leader7Rematch_LastSwitchIn, sText_Leader7Rematch_LowHp}, // Gym Leader Iris Rematch
	{558, sText_Leader8Rematch_FirstMonDown, sText_Leader8Rematch_LastSwitchIn, sText_Leader8Rematch_LowHp}, // Gym Leaders Dennis & Dee Rematch
	{559, sText_Leader8Rematch_FirstMonDown, sText_Leader8Rematch_LastSwitchIn, sText_Leader8Rematch_LowHp}, // Gym Leaders Dennis & Dee Rematch
	{560, sText_Leader8Rematch_FirstMonDown, sText_Leader8Rematch_LastSwitchIn, sText_Leader8Rematch_LowHp}, // Gym Leaders Dennis & Dee Rematch
	{561, sText_Leader8Rematch_FirstMonDown, sText_Leader8Rematch_LastSwitchIn, sText_Leader8Rematch_LowHp}, // Gym Leaders Dennis & Dee Rematch
	{0x233, sText_KurtisRoute13Cave_FirstMonDown, sText_KurtisRoute13Cave_LastSwitchIn, sText_KurtisRoute13Cave_LowHP}, //  Pluto Leader Kurtis (Route 13 Cave)
	{564, sText_HannahRematch_FirstMonDown, sText_HannahRematch_LastSwitchIn, sText_HannahRematch_LowHP}, // Elite Four Hannah Rematch
	{565, sText_LucasRematch_FirstMonDown, sText_LucasRematch_LastSwitchIn, sText_LucasRematch_LowHP}, // Elite Four Lucas Rematch
	{566, sText_JennaRematch_FirstMonDown, sText_JennaRematch_LastSwitchIn, sText_JennaRematch_LowHP}, // Elite Four Jenna Rematch
	{567, sText_ThomasRematch_FirstMonDown, sText_ThomasRematch_LastSwitchIn, sText_ThomasRematch_LowHP}, // Elite Four Thomas Rematch
	{568, sText_TitleDefense_Rival_FirstMonDown, sText_TitleDefense_Rival_LastSwitchIn, sText_TitleDefense_Rival_LowHP}, // Title Defense (Rival, Vaporeon)
	{569, sText_TitleDefense_Rival_FirstMonDown, sText_TitleDefense_Rival_LastSwitchIn, sText_TitleDefense_Rival_LowHP}, // Title Defense (Rival, Jolteon)
	{570, sText_TitleDefense_Rival_FirstMonDown, sText_TitleDefense_Rival_LastSwitchIn, sText_TitleDefense_Rival_LowHP}, // Title Defense (Rival, Flareon)
	{571, sText_TitleDefense_Rival_FirstMonDown, sText_TitleDefense_Rival_LastSwitchIn, sText_TitleDefense_Rival_LowHP}, // Title Defense (Rival, Espeon)
	{572, sText_TitleDefense_Rival_FirstMonDown, sText_TitleDefense_Rival_LastSwitchIn, sText_TitleDefense_Rival_LowHP}, // Title Defense (Rival, Umbreon)
	{573, sText_TitleDefense_Rival_FirstMonDown, sText_TitleDefense_Rival_LastSwitchIn, sText_TitleDefense_Rival_LowHP}, // Title Defense (Rival, Leafeon)
	{574, sText_TitleDefense_Rival_FirstMonDown, sText_TitleDefense_Rival_LastSwitchIn, sText_TitleDefense_Rival_LowHP}, // Title Defense (Rival, Glaceeon)
	{575, sText_TitleDefense_Rival_FirstMonDown, sText_TitleDefense_Rival_LastSwitchIn, sText_TitleDefense_Rival_LowHP}, // Title Defense (Rival, Sylveon)
	{576, sText_TitleDefense_Joey_FirstMonDown, sText_TitleDefense_Joey_LastSwitchIn, sText_TitleDefense_Joey_LowHP}, // Title Defense (Joey)
	{577, sText_TitleDefense_Selene_FirstMonDown, sText_TitleDefense_Selene_LastSwitchIn, sText_TitleDefense_Selene_LowHP}, // Title Defense (Selene, before Victini gift)
	{578, sText_TitleDefense_Selene_FirstMonDown, sText_TitleDefense_Selene_LastSwitchIn, sText_TitleDefense_Selene_LowHP}, // Title Defense (Selene, after Victini gift)
	{579, sText_TitleDefense_Alistair_FirstMonDown, sText_TitleDefense_Alistair_LastSwitchIn, sText_TitleDefense_Alistair_LowHP}, // Title Defense (Alistair)
	{580, sText_TitleDefense_Hawthorne_FirstMonDown, sText_TitleDefense_Hawthorne_LastSwitchIn, sText_TitleDefense_Hawthorne_LowHP}, // Title Defense (Hawthorne)
	{581, sText_TitleDefense_Clancy_FirstMonDown, sText_TitleDefense_Clancy_LastSwitchIn, sText_TitleDefense_Clancy_LowHP}, // Title Defense (Clancy)
	{582, sText_TitleDefense_Ena_FirstMonDown, sText_TitleDefense_Ena_LastSwitchIn, sText_TitleDefense_Ena_LowHP}, // Title Defense (Ena)
	{583, sText_TitleDefense_Copycat_FirstMonDown, sText_TitleDefense_Copycat_LastSwitchIn, sText_TitleDefense_Copycat_LowHP}, // Title Defense (Copycat, Male)
	{584, sText_TitleDefense_Copycat_FirstMonDown, sText_TitleDefense_Copycat_LastSwitchIn, sText_TitleDefense_Copycat_LowHP}, // Title Defense (Copycat, Female)
	{585, sText_TitleDefense_Foreigner_FirstMonDown, sText_TitleDefense_Foreigner_LastSwitchIn, sText_TitleDefense_Foreigner_LowHP}, // Title Defense (Foreigner)
	{586, sText_TitleDefense_Collin_FirstMonDown, sText_TitleDefense_Collin_LastSwitchIn, sText_TitleDefense_Collin_LowHP}, // Title Defense (Collin)
	{587, sText_TitleDefense_Crystal_FirstMonDown, sText_TitleDefense_Crystal_LastSwitchIn, sText_TitleDefense_Crystal_LowHP}, // Title Defense (Crystal)
	{588, sText_TitleDefense_Irene_FirstMonDown, sText_TitleDefense_Irene_LastSwitchIn, sText_TitleDefense_Irene_LowHP}, // Title Defense (Irene)
	{589, sText_TitleDefense_Ronald_FirstMonDown, sText_TitleDefense_Ronald_LastSwitchIn, sText_TitleDefense_Ronald_LowHP}, // Title Defense (Ronald)
	{590, sText_TitleDefense_Kurtis_FirstMonDown, sText_TitleDefense_Kurtis_LastSwitchIn, sText_TitleDefense_Kurtis_LowHP}, // Title Defense (Kurtis)
	{591, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Postgame rival exhbition battle (Vaporeon)
	{592, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Postgame rival exhbition battle (Jolteon)
	{593, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Postgame rival exhbition battle (Flareon)
	{594, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Postgame rival exhbition battle (Espeon)
	{595, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Postgame rival exhbition battle (Umbreon)
	{596, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Postgame rival exhbition battle (Leafeon)
	{597, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Postgame rival exhbition battle (Glaceon)
	{598, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Postgame rival exhbition battle (Sylveon)
	{599, sText_Rival7_FirstMonDown, sText_Rival7_LastSwitchIn, sText_Rival7_LowHP}, // Postgame rival exhbition battle (Emraldin)
};

static const struct DynamaxTrainerSlide sDynamaxTrainerSlides[] =
{
	{0x17, gText_TestTrainerDynamaxMsg}, //Test data
	#ifdef UNBOUND
	{0x1D5, sText_RogueElectivire_DynamaxMsg},
	#endif
};

//This file's functions:
static bool8 IsBankHpLow(u8 bank);
static u8 GetEnemyMonCount(bool8 onlyAlive);

void atk53_trainerslidein(void)
{
	gActiveBattler = GetBattlerAtPosition(gBattlescriptCurrInstr[1]);
	EmitTrainerSlide(0);
	MarkBufferBankForExecution(gActiveBattler);
	gBattlescriptCurrInstr += 2;
}

void TrainerSlideInScriptingBank(void)
{
	gActiveBattler = gBattleScripting.bank;
	EmitTrainerSlide(0);
	MarkBufferBankForExecution(gActiveBattler);
}

void TrainerSlideOutScriptingBank(void)
{
	gActiveBattler = gBattleScripting.bank;
	EmitTrainerSlideBack(0);
	MarkBufferBankForExecution(gActiveBattler);
}

//The modifications made to this function don't affect
//sliding in anyway. They allow expanded Battle Backgrounds.
void HandleIntroSlide(u8 terrain)
{
	u8 taskId, bank;

	if (!AreAbilitiesSuppressed())
	{
		for (bank = 0; bank < gBattlersCount; ++bank)
		{
			if (((gBattleTypeFlags & BATTLE_TYPE_TRAINER) || SIDE(bank) == B_SIDE_PLAYER) //Wild Pokemon can't be hidden
			&& GetMonAbility(GetBankPartyData(bank)) == ABILITY_ILLUSION)
			{
				gStatuses3[bank] |= STATUS3_ILLUSION;
				if (GetIllusionPartyData(bank) == GetBankPartyData(bank)) //Is trying to hide as itself
					gStatuses3[bank] &= ~STATUS3_ILLUSION; //Remove the Illusion
			}
		}
	}

	if (gBattleTypeFlags & BATTLE_TYPE_LINK)
	{
		taskId = CreateTask(BattleIntroSlideLink, 0);
	}
	else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
	{
		taskId = CreateTask(BattleIntroSlide3, 0);
	}
	else if (terrain > BATTLE_TERRAIN_CHAMPION)
	{
		taskId = CreateTask(BattleIntroSlide3, 0);
	}
	else
	{
		taskId = CreateTask(sBattleIntroSlideFuncs[terrain], 0);
	}

	gTasks[taskId].data[0] = 0;
	gTasks[taskId].data[1] = terrain;
	gTasks[taskId].data[2] = 0;
	gTasks[taskId].data[3] = 0;
	gTasks[taskId].data[4] = 0;
	gTasks[taskId].data[5] = 0;
	gTasks[taskId].data[6] = 0;
}

static u8 GetEnemyMonCount(bool8 onlyAlive)
{
	u8 i, count = 0;

	for (i = 0; i < PARTY_SIZE; i++)
	{
		u32 species = GetMonData(&gEnemyParty[i], MON_DATA_SPECIES2, NULL);
		if (species != SPECIES_NONE
		&&  species != SPECIES_EGG
		&& (!onlyAlive || gEnemyParty[i].hp))
			++count;
	}

	return count;
}

static bool8 IsBankHpLow(u8 bank)
{
	return udivsi((gBattleMons[bank].hp * 100), gBattleMons[bank].maxHP) < 25;
}

bool8 ShouldDoTrainerSlide(u8 bank, u16 trainerId, u8 caseId)
{
	u32 i;

	if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER) || SIDE(bank) != B_SIDE_OPPONENT || gNewBS->trainerSlideTextDoneThisTurn)
		return FALSE;

	for (i = 0; i < ARRAY_COUNT(sTrainerSlides); ++i)
	{
		if (trainerId == sTrainerSlides[i].trainerId)
		{
			gBattleScripting.bank = bank;
			switch (caseId) {
				case TRAINER_SLIDE_LAST_SWITCHIN:
					if (sTrainerSlides[i].msgLastSwitchIn != NULL
					&& ((IS_SINGLE_BATTLE && GetEnemyMonCount(TRUE) == 1)
					 || (IS_DOUBLE_BATTLE && GetEnemyMonCount(TRUE) <= 2)))
					{
						gBattleStringLoader = sTrainerSlides[i].msgLastSwitchIn;

						// If the player is challenging a gym leader and they've switched in their last pokemon, change the music when their slide in text displays
						u8 class = gTrainers[gTrainerBattleOpponent_A].trainerClass;
						if ((gBattleTypeFlags & BATTLE_TYPE_TRAINER) == (BATTLE_TYPE_TRAINER)
							&& !(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_FRONTIER | BATTLE_TYPE_TRAINER_TOWER))
							&& (class == CLASS_LEADER || class == CLASS_ELITE_4 || class == CLASS_CHAMPION || class == CLASS_CHALLENGER))
							{
								PlayBGM(BGM_BATTLE_GYM_LEADER_LAST_POKEMON);
							}

						gNewBS->trainerSlideTextDoneThisTurn = TRUE; // Prevent more switch in text this turn
						return TRUE;
					}
					break;

				case TRAINER_SLIDE_LAST_LOW_HP:
					if (sTrainerSlides[i].msgLastLowHp != NULL
					&& GetEnemyMonCount(TRUE) == 1
					&& IsBankHpLow(bank)
					&& !gNewBS->trainerSlideLowHpMsgDone)
					{
						gNewBS->trainerSlideLowHpMsgDone = TRUE;
						gBattleStringLoader = sTrainerSlides[i].msgLastLowHp;
						return TRUE;
					}
					break;

				case TRAINER_SLIDE_FIRST_DOWN:
					if (sTrainerSlides[i].msgFirstDown != NULL && GetEnemyMonCount(TRUE) == GetEnemyMonCount(FALSE) - 1)
					{
						gBattleStringLoader = sTrainerSlides[i].msgFirstDown;
						return TRUE;
					}
					break;
			}
			break;
		}
	}

	return FALSE;
}

void TryDoDynamaxTrainerSlide(void)
{
	u32 i;
	u16 trainerId;

	if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER) || SIDE(gBattleScripting.bank) != B_SIDE_OPPONENT)
		return;

	if (IsTwoOpponentBattle() && GetBattlerPosition(gBattleScripting.bank) == B_POSITION_OPPONENT_RIGHT)
		trainerId = gTrainerBattleOpponent_B;
	else
		trainerId = gTrainerBattleOpponent_A;

	gBattleStringLoader = gText_DefaultTrainerDynamaxMsg;
	for (i = 0; i < NELEMS(sDynamaxTrainerSlides); ++i)
	{
		if (trainerId == sDynamaxTrainerSlides[i].trainerId)
			gBattleStringLoader = sDynamaxTrainerSlides[i].dynamaxMsg;
	}

	// //Try giving any Trainer named "Red" a special string
	// if (i >= NELEMS(sDynamaxTrainerSlides))
	// {
	// 	u8 redName[] = {CHAR_R, CHAR_e, CHAR_d, EOS};

	// 	if (StringCompare(GetTrainerName(gBattleScripting.bank), redName) == 0) //Trainer's name is "Red"
	// 		gBattleStringLoader = gText_RedDynamaxMsg;
	// }

	BattleScriptPush(gBattlescriptCurrInstr + 5); //After callasm
	gBattlescriptCurrInstr = BattleScript_TrainerSlideMsgRet - 5;
}

//Hook in Battle Main; runs from BattleTurnPassed, i.e. once at every turn boundary from turn 2 on
void CheckLastMonLowHPSlide(void)
{
	gNewBS->trainerSlideTextDoneThisTurn = FALSE;

	if (ShouldDoTrainerSlide(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), gTrainerBattleOpponent_A, TRAINER_SLIDE_LAST_LOW_HP)
	|| (IsTwoOpponentBattle() && ShouldDoTrainerSlide(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT), gTrainerBattleOpponent_B, TRAINER_SLIDE_LAST_LOW_HP))
	|| (IS_DOUBLE_BATTLE && ShouldDoTrainerSlide(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT), gTrainerBattleOpponent_A, TRAINER_SLIDE_LAST_LOW_HP)))
		BattleScriptExecute(BattleScript_TrainerSlideMsgEnd2);
}

//handletrainerslidemsg BANK CASE
void atkFF1C_handletrainerslidemsg(void)
{
	//The trainer picture is drawn over this bank's mon graphics and sprite slot, so this has to be the
	//same bank the slide runs on. Repairing a different one leaves the real mon as a ghost on screen.
	gActiveBattler = GetBankForBattleScript(gBattlescriptCurrInstr[1]);

	u8 caseId = gBattlescriptCurrInstr[2];

	switch(caseId) {
		case 0:
			gNewBS->trainerSlideInProgress = TRUE; //Prevent's the foe's shadow from having problems
			gNewBS->savedObjId = gBattlerSpriteIds[gActiveBattler];
			break;

		case 1:
			gNewBS->trainerSlideInProgress = FALSE;
			gBattlerSpriteIds[gActiveBattler] = gNewBS->savedObjId;
			if (BATTLER_ALIVE(gActiveBattler))
				BattleLoadOpponentMonSpriteGfx(GetBankPartyData(gActiveBattler), gActiveBattler);
	}

	gBattlescriptCurrInstr += 3;
}

//trytrainerslidefirstdownmsg BANK
void atkFF1D_trytrainerslidefirstdownmsg(void)
{
	u8 pos, shouldDo;

	gActiveBattler = GetBankForBattleScript(gBattlescriptCurrInstr[1]);
	pos = GetBattlerPosition(gActiveBattler);

	if (IsTwoOpponentBattle() && pos == B_POSITION_OPPONENT_RIGHT)
		shouldDo = ShouldDoTrainerSlide(gActiveBattler, gTrainerBattleOpponent_B, TRAINER_SLIDE_FIRST_DOWN);
	else
		shouldDo = ShouldDoTrainerSlide(gActiveBattler, gTrainerBattleOpponent_A, TRAINER_SLIDE_FIRST_DOWN);

	if (shouldDo)
	{
		BattleScriptPush(gBattlescriptCurrInstr + 2);
		gBattlescriptCurrInstr = BattleScript_TrainerSlideMsgRet;
		return;
	}

	gBattlescriptCurrInstr += 2;
}

void atkFF1E_trainerslideout(void)
{
	gActiveBattler = GetBattlerAtPosition(gBattlescriptCurrInstr[1]);
	EmitTrainerSlideBack(0);
	MarkBufferBankForExecution(gActiveBattler);
	gBattlescriptCurrInstr += 2;
}
