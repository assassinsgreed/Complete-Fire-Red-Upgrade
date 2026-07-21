#include "defines.h"
#include "defines_battle.h"
#include "../include/event_data.h"
#include "../include/wild_encounter.h"
#include "../include/wild_pokemon_area.h"

#include "../include/constants/maps.h"
#include "../include/constants/region_map_sections.h"
#include "../include/constants/vars.h"

#include "../include/new/dns.h"

// Taken data from decomp: https://github.com/pret/pokefirered/blob/master/src/wild_pokemon_area.c

extern const struct WildPokemonHeader gWildMonMorningHeaders[];
extern const struct WildPokemonHeader gWildMonEveningHeaders[];
extern const struct WildPokemonHeader gWildMonNightHeaders[];

extern const struct WildPokemonHeader gDivergentWildMonDefaultHeaders[];
extern const struct WildPokemonHeader gDivergentWildMonEveningNightHeaders[];

static const u16 sDexAreas_Kulure[][2] = {
    { MAPSEC_ANTHRA_TOWN,          1 },
    { MAPSEC_OLENIC_TOWN,          2 },
    { MAPSEC_RHODANZI_CITY,        3 },
    { MAPSEC_FERROX_VILLAGE,       4 },
    { MAPSEC_HELEO_CITY,           5 },
    { MAPSEC_DAIMYN_CITY,          6 },
    { MAPSEC_LAPLAZ_TOWN,          7 },
    { MAPSEC_BRUCCIE_VILLAGE,      8 },
    { MAPSEC_EMRALDIN_QUAY,        9 },
    { MAPSEC_TSARVOSA_CITY,       10 },
    { MAPSEC_UTEYA_VILLAGE,       11 },
    { MAPSEC_ROUTE_11_NORTH,      15 },
    { MAPSEC_ROUTE_12_WEST,       53 },
    { MAPSEC_ROUTE_1,             12 },
    { MAPSEC_ROUTE_2,             13 },
    { MAPSEC_ROUTE_3,             14 },
    { MAPSEC_ROUTE_4,             54 },
    { MAPSEC_ROUTE_5,             16 },
    { MAPSEC_ROUTE_6,             17 },
    { MAPSEC_ROUTE_7,             18 },
    { MAPSEC_ROUTE_8,             19 },
    { MAPSEC_ROUTE_9,             20 },
    { MAPSEC_ROUTE_10,            21 },
    { MAPSEC_ROUTE_11_SOUTH,      22 },
    { MAPSEC_ROUTE_12_REST_HOUSE, 23 },
    { MAPSEC_ROUTE_13_REST_HOUSE, 24 },
    { MAPSEC_ROUTE_14,            25 },
    { MAPSEC_ROUTE_15_NORTH,      26 },
    { MAPSEC_ROUTE_16,            27 },
    { MAPSEC_ROUTE_17,            28 },
    { MAPSEC_ROUTE_18,            29 },
    { MAPSEC_ROUTE_19,            30 },
    { MAPSEC_ROUTE_20,            31 },
    { MAPSEC_ROUTE_21,            32 },
    { MAPSEC_ROUTE_22,            33 },
    { MAPSEC_ROUTE_23,            34 },
    { MAPSEC_ROUTE_24,            35 },
    { MAPSEC_ROUTE_13,            36 },
    { MAPSEC_VARISI_FOREST,       37 },
    { MAPSEC_RUBARR_DESERT,       38 },
    { MAPSEC_TORMA_CAVE,          39 },
    { MAPSEC_HELEO_RANCH,         40 },
    { MAPSEC_FORGOTTEN_MANSE,     41 },
    { MAPSEC_LAKE_LAPLAZ,         42 },
    { MAPSEC_PERADON_FOREST,      43 },
    { MAPSEC_CARNELIDGE_VOLCANO,  44 },
    { MAPSEC_SEPPIRE_COVE,        45 },
    { MAPSEC_ORICHELLE_GARDEN,    46 },
    { MAPSEC_MIMMETT_JUNGLE,      47 },
    { MAPSEC_VICTORY_ROAD,        48 },
    { MAPSEC_HESSON_PASS,         49 }, 
    { MAPSEC_UTEYAN_RUINS,        50 },
    { MAPSEC_DAIMYN_FACTORY,      52 },
    { MAPSEC_ROUTE_12_EAST,       51 },
};

// Formerly Sevii Island 1
static const u16 sDexAreas_KulureExpanded1[][2] = {
	{ MAPSEC_SCALDING_SPA,    55 },
	{ MAPSEC_CALICIN_BAY,     57 },
};

// Formerly Sevii Island 2
static const u16 sDexAreas_KulureExpanded2[][2] = {
	{ MAPSEC_SECRET_TRAIL, 32 }, // Same as Route 21
	{ MAPSEC_PLUTO_HQ,     49 }
};

// Formerly Sevii Island 3
static const u16 sDexAreas_KulureExpanded3[][2] = {
	{ MAPSEC_ROUTE_15_SOUTH,    56 },
};

static const struct
{
    const u16 (*table)[2];
    s32 count;
} sKulureExpandedDexAreas[] = {
    { sDexAreas_KulureExpanded1, ARRAY_COUNT(sDexAreas_KulureExpanded1) },
    { sDexAreas_KulureExpanded2, ARRAY_COUNT(sDexAreas_KulureExpanded2) },
    { sDexAreas_KulureExpanded3, ARRAY_COUNT(sDexAreas_KulureExpanded3) }
};

// Ditto, Rotom, Victini, Jirachi and every species with a Dex entry >= 300 are
// shared between standard and divergent modes. These live only in the standard
// encounter tables (they were never duplicated into the divergent file), so in
// divergent mode the Area screen must fall back to the standard tables for them.
// A species NOT in this set is mode-specific: in divergent mode it should only
// ever surface from the divergent tables, never from the standard fallback.
static bool8 IsSharedAreaSpecies(u16 species)
{
    switch (species)
    {
    case SPECIES_DITTO:
    case SPECIES_ROTOM:
    case SPECIES_VICTINI:
    case SPECIES_JIRACHI:
        return TRUE;
    }

    return SpeciesToNationalPokedexNum(species) >= 300;
}

// Scans one mode's encounter tables for the given species and writes its area
// markers into 'subsprites', returning the number of areas found. The caller
// resets 'subsprites' by passing a fresh count-0 scan, so a later scan safely
// overwrites the markers of an earlier scan that found nothing.
static s32 ScanAreaMarkers(u16 species, struct Subsprite * subsprites, bool8 useDivergentTables)
{
    s32 areaCount;
    s32 mapSecId;
    u16 dexArea;
    s32 tableIndex;
    u32 i, j;
    bool8 foundInExpandedEncounterTables;

    const struct WildPokemonHeader* headerTable;
    // The mode's day/default table, used as the fallback for maps with no
    // time-specific entry when it isn't currently daytime.
    const struct WildPokemonHeader* dayFallbackTable;

    if (useDivergentTables)
    {
        dayFallbackTable = gDivergentWildMonDefaultHeaders;
        if (IsEvening() || IsNightTime())
            headerTable = gDivergentWildMonEveningNightHeaders;
        else
            headerTable = gDivergentWildMonDefaultHeaders;
    }
    else
    {
        dayFallbackTable = gWildMonHeaders;
        if (IsNightTime())
            headerTable = gWildMonNightHeaders;
        else if (IsMorning())
            headerTable = gWildMonMorningHeaders;
        else if (IsEvening())
            headerTable = gWildMonEveningHeaders;
        else // daytime
            headerTable = gWildMonHeaders;
    }

    for (i = 0, areaCount = 0; headerTable[i].mapGroup != MAP_GROUP(UNDEFINED); i++)
    {
        foundInExpandedEncounterTables = FALSE;
        mapSecId = GetMapSecIdFromWildMonHeader(&headerTable[i]);

        if (IsSpeciesOnMap(&headerTable[i], species))
        {
            for (j = 0; j < ARRAY_COUNT(sKulureExpandedDexAreas); j++)
            {
                tableIndex = 0;
                while (FindDexAreaByMapSec(mapSecId, sKulureExpandedDexAreas[j].table, sKulureExpandedDexAreas[j].count, &tableIndex, &dexArea))
                {
                    if (dexArea != DEX_AREA_NONE)
                    {
                        GetAreaMarkerSubsprite(areaCount++, dexArea, subsprites);
                        foundInExpandedEncounterTables = TRUE;
                    }
                }
            }

            // Search for all dex areas associated with this MAPSEC.
            // In the vanilla game each MAPSEC only has at most one DEX_AREA.
            if (!foundInExpandedEncounterTables)
            {
                tableIndex = 0;
                while (FindDexAreaByMapSec(mapSecId, sDexAreas_Kulure, ARRAY_COUNT(sDexAreas_Kulure), &tableIndex, &dexArea))
                {
                    if (dexArea != DEX_AREA_NONE)
                        GetAreaMarkerSubsprite(areaCount++, dexArea, subsprites);
                }
            }
        }
    }

    // If not daytime, iterate through the day fallback table and skip entries that exist in headerTable
    if (!IsOnlyDayTime())
    {
        for (i = 0; dayFallbackTable[i].mapGroup != MAP_GROUP(UNDEFINED); i++)
        {
            bool8 skipEntry = FALSE;
            for (j = 0; headerTable[j].mapGroup != MAP_GROUP(UNDEFINED); j++)
            {
                if (dayFallbackTable[i].mapGroup == headerTable[j].mapGroup &&
                    dayFallbackTable[i].mapNum == headerTable[j].mapNum)
                {
                    skipEntry = TRUE;
                    break;
                }
            }

            if (skipEntry)
                continue;

            foundInExpandedEncounterTables = FALSE;
            mapSecId = GetMapSecIdFromWildMonHeader(&dayFallbackTable[i]);

            if (IsSpeciesOnMap(&dayFallbackTable[i], species))
            {
                for (j = 0; j < ARRAY_COUNT(sKulureExpandedDexAreas); j++)
                {
                    tableIndex = 0;
                    while (FindDexAreaByMapSec(mapSecId, sKulureExpandedDexAreas[j].table, sKulureExpandedDexAreas[j].count, &tableIndex, &dexArea))
                    {
                        if (dexArea != DEX_AREA_NONE)
                        {
                            GetAreaMarkerSubsprite(areaCount++, dexArea, subsprites);
                            foundInExpandedEncounterTables = TRUE;
                        }
                    }
                }

                if (!foundInExpandedEncounterTables)
                {
                    tableIndex = 0;
                    while (FindDexAreaByMapSec(mapSecId, sDexAreas_Kulure, ARRAY_COUNT(sDexAreas_Kulure), &tableIndex, &dexArea))
                    {
                        if (dexArea != DEX_AREA_NONE)
                            GetAreaMarkerSubsprite(areaCount++, dexArea, subsprites);
                    }
                }
            }
        }
    }

    return areaCount;
}

// Scans for the given species and populates 'subsprites' with the area markers.
// Returns the number of areas where the species was found.
// Revised for time-based and CFRU injected encounters.
s32 GetSpeciesPokedexAreaMarkers(u16 species, struct Subsprite * subsprites)
{
    s32 areaCount;

    if (GetRoamerIndex(species) >= 0)
        return GetRoamerPokedexAreaMarkers(species, subsprites);

    if (FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS))
    {
        // In divergent mode a species is placed in the divergent tables no
        // matter its Dex number, so scan those first. Only if it is absent
        // there AND it is a shared species (never duplicated into the divergent
        // file) do we fall back to the standard tables. A mode-specific species
        // that is missing from the divergent tables correctly shows nothing.
        areaCount = ScanAreaMarkers(species, subsprites, TRUE);
        if (areaCount == 0 && IsSharedAreaSpecies(species))
            areaCount = ScanAreaMarkers(species, subsprites, FALSE);

        return areaCount;
    }

    return ScanAreaMarkers(species, subsprites, FALSE);
}