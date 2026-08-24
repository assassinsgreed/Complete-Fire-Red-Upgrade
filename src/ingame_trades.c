#include "../include/global.h"
#include "../include/ingame_trades.h"
#include "../include/link.h"
#include "../include/pokemon.h"
#include "../include/string_util.h"
#include "../include/trade.h"
#include "../include/constants/moves.h"
#include "config.h"

#include "../include/new/build_pokemon.h"
#include "../include/new/rom_locs.h"
#include "../include/new/Vanilla_functions_battle.h"

#include "../include/constants/region_map_sections.h"
#include "../include/constants/species.h"
#include "../include/constants/items.h"
#include "../include/new/util.h"
#include "../include/new/catching.h"
#include "defines_battle.h" // For Rival name lookup
#include "../include/new/mega.h" // For Rival name lookup

extern struct TradeAnimationResources * sTradeData;

extern u8 gText_InGameTrade_Cosmo[];
extern u8 gText_InGameTrade_OTMillie[];
extern u8 gText_InGameTrade_Pikachu[];
extern u8 gText_InGameGift_OTAsh[];
extern u8 gText_InGameTrade_Mimmers[];
extern u8 gText_InGameTrade_Drago[];
extern u8 gText_InGameTrade_Cork[];
extern u8 gText_InGameTrade_Lacey[];
extern u8 gText_InGameTrade_Pinky[];
extern u8 gText_InGameTrade_Pip[];
extern u8 gText_InGameTrade_Boomer[];
extern u8 gText_InGameTrade_Strawberry[];
extern u8 gText_InGameTrade_OTSylvestre[];
extern u8 gText_InGameTrade_Rocky[];
extern u8 gText_InGameTrade_Chopper[];
extern u8 gText_InGameTrade_Autumn[];
extern u8 gText_InGameTrade_OTRival[];
extern u8 gText_InGameTrade_Boris[];
extern u8 gText_InGameTrade_OTWinona[];
extern u8 gText_InGameGift_OTSelene[];
extern u8 gText_InGameGift_Victini[];
extern u8 gText_InGameGift_OTAether[];
extern u8 gText_InGameGift_TypeNull[];
extern u8 gText_InGameGift_OTBelle[];
extern u8 gText_InGameGift_Piki[];

// Divergent nicknames
extern u8 gText_InGameTrade_Divergent_Tommy[];
extern u8 gText_InGameTrade_Divergent_Diva[];
extern u8 gText_InGameTrade_Divergent_Otto[];
extern u8 gText_InGameTrade_Divergent_Tsu[];
extern u8 gText_InGameTrade_Divergent_Peeks[];
extern u8 gText_InGameTrade_Divergent_Chompy[];
extern u8 gText_InGameTrade_Divergent_Bruce[];
extern u8 gText_InGameTrade_Divergent_Raspberry[];
extern u8 gText_InGameTrade_Divergent_Cookie[];
extern u8 gText_InGameTrade_Divergent_Pascal[];
extern u8 gText_InGameTrade_Divergent_Tina[];

static const struct InGameTrade sInGameTrades[] = {
    [INGAME_TRADE_CHINCHOU] = 
    {
        .nickname = gText_InGameTrade_Cosmo,
        .species = SPECIES_CHINCHOU,
        .ivs = {20, 15, 18, 25, 23, 22},
        .abilityNum = 0, // Volt Absorb
        .otId = 1999,
        .conditions = {5, 5, 5, 30, 5},
        .personality = 0x00009cae,
        .heldItem = ITEM_NONE,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTMillie,
        .otGender = FEMALE,
        .nature = NATURE_CALM,
        .requestedSpecies = SPECIES_SNOM
    },
    [INGAME_TRADE_MR_MIME] = {
        .nickname = gText_InGameTrade_Mimmers,
        .species = SPECIES_MR_MIME_G,
        .ivs = {18, 21, 24, 26, 15, 16},
        .abilityNum = 0, // Screen Cleaner
        .otId = 90210,
        .conditions = {10, 15, 10, 30, 5},
        .personality = 0x498a2e1d,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_BASHFUL,
        .requestedSpecies = SPECIES_FARFETCHD_G
    },
    [INGAME_TRADE_DRATINI] = {
        .nickname = gText_InGameTrade_Drago,
        .species = SPECIES_DRATINI,
        .ivs = {15, 28, 18, 17, 22, 24},
        .abilityNum = 0, // Shed Skin
        .otId = 90210,
        .conditions = {20, 10, 20, 20, 30},
        .personality = 0x4c970b89,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_JOLLY,
        .requestedSpecies = SPECIES_BONSLY
    },
    [INGAME_TRADE_CORSOLA_G] = {
        .nickname = gText_InGameTrade_Cork,
        .species = SPECIES_CORSOLA_G,
        .ivs = {30, 12, 22, 20, 17, 2},
        .abilityNum = 0, // Weak Armor
        .otId = 90210,
        .conditions = {5, 15, 15, 10, 20},
        .personality = 0x151943d7,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_TIMID,
        .requestedSpecies = SPECIES_SLAKOTH
    },
    [INGAME_TRADE_FRILLISH] = {
        .nickname = gText_InGameTrade_Lacey,
        .species = SPECIES_FRILLISH_F,
        .ivs = {24, 18, 20, 25, 31, 15},
        .abilityNum = 1, // Cursed body
        .otId = 90210,
        .conditions = {10, 10, 5, 10, 15},
        .personality = 0x00eeca15,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_CALM,
        .requestedSpecies = SPECIES_MAGIKARP
    },
    [INGAME_TRADE_EMOLGA] = {
        .nickname = gText_InGameTrade_Pinky,
        .species = SPECIES_EMOLGA,
        .ivs = {12, 18, 15, 27, 22, 30},
        .abilityNum = 0, // Static
        .otId = 90210,
        .conditions = {15, 20, 5, 5, 30},
        .personality = 0x451308ab,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_JOLLY,
        .requestedSpecies = SPECIES_BOLDORE
    },
    [INGAME_TRADE_EEVEE] = {
        .nickname = gText_InGameTrade_Pip,
        .species = SPECIES_EEVEE,
        .ivs = {20, 20, 20, 20, 20, 25},
        .abilityNum = 1, // Adaptability
        .otId = 90210,
        .conditions = {20, 20, 10, 10, 15},
        .personality = 0x06341016,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_IMPISH,
        .requestedSpecies = SPECIES_RIOLU
    },
    [INGAME_TRADE_NOIBAT] = {
        .nickname = gText_InGameTrade_Boomer,
        .species = SPECIES_NOIBAT,
        .ivs = {22, 18, 13, 24, 21, 28},
        .abilityNum = 0, // Frisk
        .otId = 90210,
        .conditions = {5, 5, 25, 20, 15},
        .personality = 0x5c77ecfa,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_SASSY,
        .requestedSpecies = SPECIES_LILLIPUP
    },
    [INGAME_TRADE_HATENNA] = {
        .nickname = gText_InGameTrade_Strawberry,
        .species = SPECIES_HATENNA,
        .ivs = {28, 7, 14, 23, 26, 12},
        .abilityNum = 0, // Healer
        .otId = 90210,
        .conditions = {10, 5, 10, 15, 30},
        .personality = 0x5c77ecfa,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_MODEST,
        .requestedSpecies = SPECIES_CACNEA
    },
    [INGAME_TRADE_BOLDORE] = {
        .nickname = gText_InGameTrade_Rocky,
        .species = SPECIES_BOLDORE,
        .ivs = {24, 17, 26, 8, 23, 13},
        .abilityNum = 0xFF, // Sand Force (Hidden)
        .otId = 35846,
        .conditions = {15, 15, 20, 10, 25},
        .personality = 0x451308ab,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTRival,
        .otGender = MALE,
        .nature = NATURE_IMPISH,
        .requestedSpecies = SPECIES_NONE // Species check is skipped
    },
    [INGAME_TRADE_GURDURR] = {
        .nickname = gText_InGameTrade_Chopper,
        .species = SPECIES_GURDURR,
        .ivs = {25, 29, 22, 10, 18, 5},
        .abilityNum = 0xFF, // Iron Fist (Hidden)
        .otId = 35846,
        .conditions = {30, 25, 10, 15, 10},
        .personality = 0x451308ab,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTRival,
        .otGender = MALE,
        .nature = NATURE_ADAMANT,
        .requestedSpecies = SPECIES_NONE // Species check is skipped
    },
    [INGAME_TRADE_PHANTUMP] = {
        .nickname = gText_InGameTrade_Autumn,
        .species = SPECIES_PHANTUMP,
        .ivs = {23, 18, 26, 17, 22, 16},
        .abilityNum = 0xFF, // Harvest (Hidden)
        .otId = 35846,
        .conditions = {20, 15, 15, 10, 25},
        .personality = 0x451308ab,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTRival,
        .otGender = MALE,
        .nature = NATURE_JOLLY,
        .requestedSpecies = SPECIES_NONE // Species check is skipped
    },
    [INGAME_TRADE_SLOWBRO_G] = {
        .nickname = gText_InGameTrade_Boris,
        .species = SPECIES_SLOWBRO_G,
        .ivs = {28, 20, 18, 26, 23, 8},
        .abilityNum = 0xFF, // Regenerator (Hidden)
        .otId = 79525,
        .conditions = {5, 10, 10, 25, 20},
        .personality = 0x4c970b89,
        .heldItem = ITEM_LAGGING_TAIL,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTWinona,
        .otGender = FEMALE,
        .nature = NATURE_BOLD,
        .requestedSpecies = SPECIES_SLOWBRO
    }
};

static const struct InGameTrade sInGameGifts[] = {
    [INGAME_GIFT_PIKACHU_ORIGINAL_CAP] =
    {
        .nickname = gText_InGameTrade_Pikachu,
        .species = SPECIES_PIKACHU_CAP_ORIGINAL,
        .ivs = {25, 15, 20, 31, 25, 31},
        .abilityNum = 0, // Static
        .otId = 1997,
        .conditions = {5, 5, 15, 15, 30},
        .personality = 0x482cac89, // TODO: Investigate this
        .heldItem = ITEM_LIGHT_BALL,
        .mailNum = 0,
        .otName = gText_InGameGift_OTAsh,
        .otGender = MALE,
        .nature = NATURE_TIMID
    },
    [INGAME_GIFT_VICTINI] =
    {
        .nickname = gText_InGameGift_Victini,
        .species = SPECIES_VICTINI,
        .ivs = {26, 31, 24, 31, 27, 31},
        .abilityNum = 0, // Victory Star
        .otId = 2022,
        .conditions = {30, 30, 20, 25, 20},
        .personality = 0x451308ab,
        .heldItem = ITEM_WHITE_HERB,
        .mailNum = 0,
        .otName = gText_InGameGift_OTSelene,
        .otGender = FEMALE,
        .nature = NATURE_ADAMANT
    },
    [INGAME_GIFT_TYPE_NULL] =
    {
        .nickname = gText_InGameGift_TypeNull,
        .species = SPECIES_TYPE_NULL,
        .ivs = {31, 30, 26, 31, 25, 31},
        .abilityNum = 0, // Battle Armor
        .otId = 81116,
        .conditions = {25, 30, 30, 15, 20},
        .personality = 0x4c970b89,
        .heldItem = ITEM_NONE,
        .mailNum = 0,
        .otName = gText_InGameGift_OTAether,
        .otGender = MALE,
        .nature = NATURE_TIMID
    },
    [INGAME_GIFT_PIKACHU_COSPLAY] =
    {
        .nickname = gText_InGameGift_Piki,
        .species = SPECIES_PIKACHU_POP_STAR,
        .ivs = {30, 25, 26, 31, 28, 30},
        .abilityNum = 0, // Static
        .otId = 20141,
        .conditions = {30, 30, 30, 30, 30},
        .personality = 0x3d5f21ce,
        .heldItem = ITEM_LIGHT_BALL,
        .mailNum = 0,
        .otName = gText_InGameGift_OTBelle,
        .otGender = FEMALE,
        .nature = NATURE_TIMID
    }
};

// Divergent trades
static const struct InGameTrade sInGameTrades_Divergent[] = {
    [INGAME_TRADE_DIVERGENT_EELEKTRIK] = 
    {
        .nickname = gText_InGameTrade_Divergent_Tommy,
        .species = SPECIES_EELEKTRIK,
        .ivs = {23, 12, 19, 23, 29, 17},
        .abilityNum = 1, // Levitate
        .otId = 1999,
        .conditions = {5, 5, 5, 30, 5},
        .personality = 0x00009cae,
        .heldItem = ITEM_NONE,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTMillie,
        .otGender = FEMALE,
        .nature = NATURE_BOLD,
        .requestedSpecies = SPECIES_VANILLITE
    },
    [INGAME_TRADE_DIVERGENT_JYNX] = {
        .nickname = gText_InGameTrade_Divergent_Diva,
        .species = SPECIES_JYNX,
        .ivs = {21, 18, 25, 28, 12, 19},
        .abilityNum = 0, // Oblivious
        .otId = 90210,
        .conditions = {10, 15, 10, 30, 5},
        .personality = 0x498a2e1d,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_TIMID,
        .requestedSpecies = SPECIES_POLIWHIRL
    },
    [INGAME_TRADE_DIVERGENT_XATU] = {
        .nickname = gText_InGameTrade_Divergent_Otto,
        .species = SPECIES_XATU,
        .ivs = {23, 22, 19, 21, 15, 19},
        .abilityNum = 0, // Synchronize
        .otId = 90210,
        .conditions = {20, 10, 20, 20, 30},
        .personality = 0x4c970b89,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_MODEST,
        .requestedSpecies = SPECIES_HAUNTER
    },
    [INGAME_TRADE_DIVERGENT_MAKUHITA] = {
        .nickname = gText_InGameTrade_Divergent_Tsu,
        .species = SPECIES_MAKUHITA,
        .ivs = {29, 15, 19, 19, 24, 9},
        .abilityNum = 0, // Thick Fat
        .otId = 90210,
        .conditions = {5, 15, 15, 10, 20},
        .personality = 0x151943d7,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_BRAVE,
        .requestedSpecies = SPECIES_SENTRET
    },
    [INGAME_TRADE_DIVERGENT_HAUNTER] = {
        .nickname = gText_InGameTrade_Divergent_Peeks,
        .species = SPECIES_HAUNTER,
        .ivs = {12, 17, 24, 27, 25, 19},
        .abilityNum = 0, // Levitate
        .otId = 90210,
        .conditions = {10, 10, 5, 10, 15},
        .personality = 0x00eeca15,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_NAUGHTY,
        .requestedSpecies = SPECIES_MEDICHAM
    },
    [INGAME_TRADE_DIVERGENT_MUNCHLAX] = {
        .nickname = gText_InGameTrade_Divergent_Chompy,
        .species = SPECIES_MUNCHLAX,
        .ivs = {24, 17, 18, 9, 29, 27},
        .abilityNum = 0, // Pickup
        .otId = 90210,
        .conditions = {15, 20, 5, 5, 30},
        .personality = 0x451308ab,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_JOLLY,
        .requestedSpecies = SPECIES_DITTO
    },
    [INGAME_TRADE_DIVERGENT_STEELIX] = {
        .nickname = gText_InGameTrade_Divergent_Bruce,
        .species = SPECIES_STEELIX,
        .ivs = {17, 24, 28, 22, 16, 13},
        .abilityNum = 0, // Rock Head
        .otId = 90210,
        .conditions = {20, 20, 10, 10, 15},
        .personality = 0x06341016,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_ADAMANT,
        .requestedSpecies = SPECIES_VILEPLUME
    },
    [INGAME_TRADE_DIVERGENT_STEENEE] = {
        .nickname = gText_InGameTrade_Divergent_Raspberry,
        .species = SPECIES_STEENEE,
        .ivs = {14, 23, 17, 19, 22, 26},
        .abilityNum = 0, // Leaf Guard
        .otId = 90210,
        .conditions = {5, 5, 25, 20, 15},
        .personality = 0x5c77ecfa,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_SASSY,
        .requestedSpecies = SPECIES_GRANBULL
    },
    [INGAME_TRADE_DIVERGENT_MEOWTH] = {
        .nickname = gText_InGameTrade_Divergent_Cookie,
        .species = SPECIES_MEOWTH,
        .ivs = {19, 27, 19, 21, 16, 22},
        .abilityNum = 0, // Pickup
        .otId = 90210,
        .conditions = {10, 5, 10, 15, 30},
        .personality = 0x5c77ecfa,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTSylvestre,
        .otGender = MALE,
        .nature = NATURE_BASHFUL,
        .requestedSpecies = SPECIES_MEOWTH_G
    },
    [INGAME_TRADE_DIVERGENT_GRAVELER_A] = {
        .nickname = gText_InGameTrade_Rocky,
        .species = SPECIES_GRAVELER_A,
        .ivs = {24, 17, 26, 8, 23, 13},
        .abilityNum = 0xFF, // Galvanize (Hidden)
        .otId = 35846,
        .conditions = {15, 15, 20, 10, 25},
        .personality = 0x451308ab,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTRival,
        .otGender = MALE,
        .nature = NATURE_IMPISH,
        .requestedSpecies = SPECIES_NONE // Species check is skipped
    },
    [INGAME_TRADE_DIVERGENT_MACHOKE] = {
        .nickname = gText_InGameTrade_Chopper,
        .species = SPECIES_MACHOKE,
        .ivs = {25, 29, 22, 10, 18, 5},
        .abilityNum = 0xFF, // Steadfast (Hidden)
        .otId = 35846,
        .conditions = {30, 25, 10, 15, 10},
        .personality = 0x451308ab,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTRival,
        .otGender = MALE,
        .nature = NATURE_ADAMANT,
        .requestedSpecies = SPECIES_NONE // Species check is skipped
    },
    [INGAME_TRADE_DIVERGENT_KADABRA] = {
        .nickname = gText_InGameTrade_Divergent_Pascal,
        .species = SPECIES_KADABRA,
        .ivs = {23, 18, 17, 26, 16, 22},
        .abilityNum = 0xFF, // Magic Guard (Hidden)
        .otId = 35846,
        .conditions = {20, 15, 15, 10, 25},
        .personality = 0x451308ab,
        .heldItem = ITEM_SITRUS_BERRY,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTRival,
        .otGender = MALE,
        .nature = NATURE_TIMID,
        .requestedSpecies = SPECIES_NONE // Species check is skipped
    },
    [INGAME_TRADE_DIVERGENT_RAPIDASH_G] = {
        .nickname = gText_InGameTrade_Divergent_Tina,
        .species = SPECIES_RAPIDASH_G,
        .ivs = {28, 24, 18, 22, 23, 8},
        .abilityNum = 0xFF, // Anticipation (Hidden)
        .otId = 79525,
        .conditions = {5, 10, 10, 25, 20},
        .personality = 0x4c970b89,
        .heldItem = ITEM_BERRY_JUICE,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTWinona,
        .otGender = FEMALE,
        .nature = NATURE_BOLD,
        .requestedSpecies = SPECIES_RAPIDASH
    }
};

extern const u16 sInGameTradeMailMessages[][10];

static void GetInGameTradeMail(struct MailStructDaycare * mail, const struct InGameTrade * inGameTrade)
{
    int i;
    for (i = 0; i < MAIL_WORDS_COUNT; i++)
        mail->words[i] = sInGameTradeMailMessages[inGameTrade->mailNum][i];
    StringCopy(mail->playerName, inGameTrade->otName);
    mail->trainerId[0] = inGameTrade->otId >> 24;
    mail->trainerId[1] = inGameTrade->otId >> 16;
    mail->trainerId[2] = inGameTrade->otId >> 8;
    mail->trainerId[3] = inGameTrade->otId;
    mail->species = inGameTrade->species;
    mail->itemId = inGameTrade->heldItem;
}

void TradeBufferOTnameAndNicknames(void)
{
    u8 nickname[20];
    u8 mpId;
    const struct InGameTrade * inGameTrade;
    if (sTradeData->isLinkTrade)
    {
        mpId = GetMultiplayerId();
        StringCopy(gStringVar1, gLinkPlayers[mpId ^ 1].name);
        GetMonData(&gEnemyParty[gSelectedTradeMonPositions[1] % 6], MON_DATA_NICKNAME, nickname);
        StringCopy_Nickname(gStringVar3, nickname);
        GetMonData(&gPlayerParty[gSelectedTradeMonPositions[0]], MON_DATA_NICKNAME, nickname);
        StringCopy_Nickname(gStringVar2, nickname);
    }
    else
    {
        inGameTrade = FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS) ? &sInGameTrades_Divergent[Var8004] : &sInGameTrades[Var8004];
        StringCopy(gStringVar1, inGameTrade->otName);
        StringCopy_Nickname(gStringVar3, inGameTrade->nickname);
        GetMonData(&gPlayerParty[Var8005], MON_DATA_NICKNAME, nickname);
        StringCopy_Nickname(gStringVar2, nickname);
    }
}

u16 GetInGameTradeSpeciesInfo(void)
{
    // Populates gStringVar1 with the name of the requested species and
    // gStringVar2 with the name of the offered species.
    // Returns the requested species.
    const struct InGameTrade * inGameTrade = FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS) ? &sInGameTrades_Divergent[Var8004] : &sInGameTrades[Var8004];
    StringCopy(gStringVar1, gSpeciesNames[inGameTrade->requestedSpecies]);
    StringCopy(gStringVar2, gSpeciesNames[inGameTrade->species]);
    return inGameTrade->requestedSpecies;
}

void BufferInGameTradeMonName(void)
{
    // Populates gStringVar1 with the nickname of the sent Pokemon and
    // gStringVar2 with the name of the offered species.
    u8 nickname[30];
    const struct InGameTrade * inGameTrade = FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS) ? &sInGameTrades_Divergent[Var8004] : &sInGameTrades[Var8004];
    GetMonData(&gPlayerParty[Var8005], MON_DATA_NICKNAME, nickname);
    StringCopy_Nickname(gStringVar1, nickname);
    StringCopy(gStringVar2, gSpeciesNames[inGameTrade->species]);
}

void CreateInGameTradePokemonInternal(u8 playerSlot, u8 inGameTradeIdx)
{
    const struct InGameTrade * inGameTrade = FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS) ? &sInGameTrades_Divergent[inGameTradeIdx] : &sInGameTrades[inGameTradeIdx];
    u8 level = GetMonData(&gPlayerParty[playerSlot], MON_DATA_LEVEL, 0);
    struct MailStructDaycare mail;
    u8 metLocation = METLOC_IN_GAME_TRADE;
    u8 mailNum;

    struct Pokemon * tradeMon = &gEnemyParty[0];
    CreateMon(tradeMon, inGameTrade->species, level, 32, TRUE, inGameTrade->personality, TRUE, inGameTrade->otId);
    SetMonData(tradeMon, MON_DATA_HP_IV, &inGameTrade->ivs[0]);
    SetMonData(tradeMon, MON_DATA_ATK_IV, &inGameTrade->ivs[1]);
    SetMonData(tradeMon, MON_DATA_DEF_IV, &inGameTrade->ivs[2]);
    SetMonData(tradeMon, MON_DATA_SPEED_IV, &inGameTrade->ivs[3]);
    SetMonData(tradeMon, MON_DATA_SPATK_IV, &inGameTrade->ivs[4]);
    SetMonData(tradeMon, MON_DATA_SPDEF_IV, &inGameTrade->ivs[5]);
    SetMonData(tradeMon, MON_DATA_NICKNAME, inGameTrade->nickname);
    // Handle Rival, who's name is not known until runtime
    if (inGameTrade->otName == gText_InGameTrade_OTRival)
    {
        const u8* name = TryGetRivalNameByTrainerClass(GET_TRAINER(1).trainerClass); // Hard coded to rival
        SetMonData(tradeMon, MON_DATA_OT_NAME, name);
    }
    else
        SetMonData(tradeMon, MON_DATA_OT_NAME, inGameTrade->otName);
    SetMonData(tradeMon, MON_DATA_OT_GENDER, &inGameTrade->otGender);
    SetMonData(tradeMon, MON_DATA_BEAUTY, &inGameTrade->conditions[1]);
    SetMonData(tradeMon, MON_DATA_CUTE, &inGameTrade->conditions[2]);
    SetMonData(tradeMon, MON_DATA_COOL, &inGameTrade->conditions[0]);
    SetMonData(tradeMon, MON_DATA_SMART, &inGameTrade->conditions[3]);
    SetMonData(tradeMon, MON_DATA_TOUGH, &inGameTrade->conditions[4]);
    SetMonData(tradeMon, MON_DATA_MET_LOCATION, &metLocation);
    GiveMonNatureAndAbility(tradeMon, inGameTrade->nature, inGameTrade->abilityNum, IsMonShiny(tradeMon), TRUE, TRUE);
    mailNum = 0;
    if (inGameTrade->heldItem != ITEM_NONE)
    {
        if (ItemIsMail(inGameTrade->heldItem))
        {
            GetInGameTradeMail(&mail, inGameTrade);
            gLinkPartnerMail[0] = mail;
            SetMonData(tradeMon, MON_DATA_MAIL, &mailNum);
            SetMonData(tradeMon, MON_DATA_HELD_ITEM, &inGameTrade->heldItem);
        }
        else
        {
            SetMonData(tradeMon, MON_DATA_HELD_ITEM, &inGameTrade->heldItem);
        }
    }
    CalculateMonStats(&gEnemyParty[0]);
}

void CreateInGameGiftPokemon()
{
    const struct InGameTrade * ingameGift = &sInGameGifts[Var8004];
    struct MailStructDaycare mail;
    u8 mailNum;
    u8 metLocation = METLOC_FATEFUL_ENCOUNTER;
    u16* moves = &Var8000; //-0x8003

    struct Pokemon * giftMon = &gEnemyParty[0];
    CreateMon(giftMon, ingameGift->species, Var8005, 32, TRUE, ingameGift->personality, TRUE, ingameGift->otId);
    SetMonData(giftMon, MON_DATA_HP_IV, &ingameGift->ivs[0]);
    SetMonData(giftMon, MON_DATA_ATK_IV, &ingameGift->ivs[1]);
    SetMonData(giftMon, MON_DATA_DEF_IV, &ingameGift->ivs[2]);
    SetMonData(giftMon, MON_DATA_SPEED_IV, &ingameGift->ivs[3]);
    SetMonData(giftMon, MON_DATA_SPATK_IV, &ingameGift->ivs[4]);
    SetMonData(giftMon, MON_DATA_SPDEF_IV, &ingameGift->ivs[5]);
    SetMonData(giftMon, MON_DATA_NICKNAME, ingameGift->nickname);
    SetMonData(giftMon, MON_DATA_OT_NAME, ingameGift->otName);
    SetMonData(giftMon, MON_DATA_OT_GENDER, &ingameGift->otGender);
    SetMonData(giftMon, MON_DATA_BEAUTY, &ingameGift->conditions[1]);
    SetMonData(giftMon, MON_DATA_CUTE, &ingameGift->conditions[2]);
    SetMonData(giftMon, MON_DATA_COOL, &ingameGift->conditions[0]);
    SetMonData(giftMon, MON_DATA_SMART, &ingameGift->conditions[3]);
    SetMonData(giftMon, MON_DATA_TOUGH, &ingameGift->conditions[4]);
    SetMonData(giftMon, MON_DATA_MET_LOCATION, &metLocation); // NOTE: When OT Name & ID don't match player, the FR engine will always set a met location of Trade
    GiveMonNatureAndAbility(giftMon, ingameGift->nature, ingameGift->abilityNum, IsMonShiny(giftMon), TRUE, TRUE);
    
    for (u8 i = 0; i < MAX_MON_MOVES; ++i)
    {
        if (moves[i] < MOVES_COUNT)
            SetMonData(giftMon, MON_DATA_MOVE1 + i, &moves[i]);
    }
    
    mailNum = 0;
    if (ingameGift->heldItem != ITEM_NONE)
    {
        if (ItemIsMail(ingameGift->heldItem))
        {
            GetInGameTradeMail(&mail, ingameGift);
            gLinkPartnerMail[0] = mail;
            SetMonData(giftMon, MON_DATA_MAIL, &mailNum);
            SetMonData(giftMon, MON_DATA_HELD_ITEM, &ingameGift->heldItem);
        }
        else
        {
            SetMonData(giftMon, MON_DATA_HELD_ITEM, &ingameGift->heldItem);
        }
    }
    CalculateMonStats(&gEnemyParty[0]);
    HealMon(giftMon);
	GiveMonToPlayer(giftMon);
    SetMonPokedexFlags(giftMon);
}
