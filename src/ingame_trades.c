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

extern struct TradeAnimationResources * sTradeData;

extern u8 gText_InGameTrade_Cosmo[];
extern u8 gText_InGameTrade_OTMillie[];
extern u8 gText_InGameTrade_Pikachu[];
extern u8 gText_InGameGift_OTAsh[];

static const struct InGameTrade sInGameTrades[] = {
    [INGAME_TRADE_CHINCHOU] = 
    {
        .nickname = gText_InGameTrade_Cosmo,
        .species = SPECIES_CHINCHOU,
        .ivs = {20, 15, 18, 25, 23, 22},
        .abilityNum = 0,
        .otId = 1999,
        .conditions = {5, 5, 5, 30, 5},
        .personality = 0x00009cae,
        .heldItem = ITEM_NONE,
        .mailNum = 0,
        .otName = gText_InGameTrade_OTMillie,
        .otGender = FEMALE,
        .nature = NATURE_CALM,
        .requestedSpecies = SPECIES_SNOM
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
        inGameTrade = &sInGameTrades[Var8004];
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
    const struct InGameTrade * inGameTrade = &sInGameTrades[Var8004];
    StringCopy(gStringVar1, gSpeciesNames[inGameTrade->requestedSpecies]);
    StringCopy(gStringVar2, gSpeciesNames[inGameTrade->species]);
    return inGameTrade->requestedSpecies;
}

void BufferInGameTradeMonName(void)
{
    // Populates gStringVar1 with the nickname of the sent Pokemon and
    // gStringVar2 with the name of the offered species.
    u8 nickname[30];
    const struct InGameTrade * inGameTrade = &sInGameTrades[Var8004];
    GetMonData(&gPlayerParty[Var8005], MON_DATA_NICKNAME, nickname);
    StringCopy_Nickname(gStringVar1, nickname);
    StringCopy(gStringVar2, gSpeciesNames[inGameTrade->species]);
}

void CreateInGameTradePokemonInternal(u8 playerSlot, u8 inGameTradeIdx)
{
    const struct InGameTrade * inGameTrade = &sInGameTrades[inGameTradeIdx];
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
