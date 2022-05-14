.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_DebugMode_Main
EventScript_DebugMode_Main:
	givepokemon SPECIES_BULBASAUR 0x32 0x0 0x0 0x0 0x0 @ lv 50 Bulbasaur
	givepokemon SPECIES_CHARMANDER 0x32 0x0 0x0 0x0 0x0 @ lv 50 Charmander
	givepokemon SPECIES_SQUIRTLE 0x32 0x0 0x0 0x0 0x0 @ lv 50 Squirtle
	givepokemon SPECIES_GROOKEY 0x32 0x0 0x0 0x0 0x0 @ lv 50 Grookey
	givepokemon SPECIES_SCORBUNNY 0x32 0x0 0x0 0x0 0x0 @ lv 50 Scorbunny
	givepokemon SPECIES_SOBBLE 0x32 0x0 0x0 0x0 0x0 @ lv 50 Sobble

	@ mark all pokemon in the dex as seen
	setvar 0x8004 SPECIES_BIDOOF
	special 0x163

	setvar 0x8004 SPECIES_BIBAREL
	special 0x163

	setvar 0x8004 SPECIES_ROOKIDEE
	special 0x163

	setvar 0x8004 SPECIES_CORVISQUIRE
	special 0x163

	setvar 0x8004 SPECIES_CORVIKNIGHT
	special 0x163

	setvar 0x8004 SPECIES_SUNKERN
	special 0x163

	setvar 0x8004 SPECIES_SUNFLORA
	special 0x163

	setvar 0x8004 SPECIES_YAMPER
	special 0x163

	setvar 0x8004 SPECIES_BOLTUND
	special 0x163

	setvar 0x8004 SPECIES_BUDEW
	special 0x163

	setvar 0x8004 SPECIES_ROSELIA
	special 0x163

	setvar 0x8004 SPECIES_ROSERADE
	special 0x163

	setvar 0x8004 SPECIES_GRUBBIN
	special 0x163

	setvar 0x8004 SPECIES_CHARJABUG
	special 0x163

	setvar 0x8004 SPECIES_VIKAVOLT
	special 0x163

	setvar 0x8004 SPECIES_ROCKRUFF
	special 0x163

	setvar 0x8004 SPECIES_LYCANROC
	special 0x163

	setvar 0x8004 SPECIES_LYCANROC_N
	special 0x163

	setvar 0x8004 SPECIES_LYCANROC_DUSK
	special 0x163

	setvar 0x8004 SPECIES_NICKIT
	special 0x163

	setvar 0x8004 SPECIES_THIEVUL
	special 0x163

	setvar 0x8004 SPECIES_NIDORAN_M
	special 0x163

	setvar 0x8004 SPECIES_NIDORINO
	special 0x163

	setvar 0x8004 SPECIES_NIDOKING
	special 0x163

	setvar 0x8004 SPECIES_BLIPBUG
	special 0x163

	setvar 0x8004 SPECIES_DOTTLER
	special 0x163

	setvar 0x8004 SPECIES_ORBEETLE
	special 0x163

	setvar 0x8004 SPECIES_PIKIPEK
	special 0x163

	setvar 0x8004 SPECIES_TRUMBEAK
	special 0x163

	setvar 0x8004 SPECIES_TOUCANNON
	special 0x163

	setvar 0x8004 SPECIES_MORELULL
	special 0x163

	setvar 0x8004 SPECIES_SHIINOTIC
	special 0x163

	setvar 0x8004 SPECIES_HOOTHOOT
	special 0x163

	setvar 0x8004 SPECIES_NOCTOWL
	special 0x163

	setvar 0x8004 SPECIES_PICHU
	special 0x163

	setvar 0x8004 SPECIES_PIKACHU
	special 0x163

	setvar 0x8004 SPECIES_PIKACHU_CAP_ORIGINAL
	special 0x163

	setvar 0x8004 SPECIES_RAICHU
	special 0x163

	setvar 0x8004 SPECIES_BUNEARY
	special 0x163

	setvar 0x8004 SPECIES_LOPUNNY
	special 0x163

	setvar 0x8004 SPECIES_LOPUNNY_MEGA
	special 0x163

	setvar 0x8004 SPECIES_SHROOMISH
	special 0x163

	setvar 0x8004 SPECIES_BRELOOM
	special 0x163

	setvar 0x8004 SPECIES_BONSLY
	special 0x163

	setvar 0x8004 SPECIES_SUDOWOODO
	special 0x163

	setvar 0x8004 SPECIES_VENIPEDE
	special 0x163

	setvar 0x8004 SPECIES_WHIRLIPEDE
	special 0x163

	setvar 0x8004 SPECIES_SCOLIPEDE
	special 0x163

	setvar 0x8004 SPECIES_SLAKOTH
	special 0x163

	setvar 0x8004 SPECIES_VIGOROTH
	special 0x163

	setvar 0x8004 SPECIES_SLAKING
	special 0x163

	setvar 0x8004 SPECIES_ZUBAT
	special 0x163

	setvar 0x8004 SPECIES_GOLBAT
	special 0x163

	setvar 0x8004 SPECIES_CROBAT
	special 0x163

	setvar 0x8004 SPECIES_DRILBUR
	special 0x163

	setvar 0x8004 SPECIES_EXCADRILL
	special 0x163

	setvar 0x8004 SPECIES_ROGGENROLA
	special 0x163

	setvar 0x8004 SPECIES_BOLDORE
	special 0x163

	setvar 0x8004 SPECIES_GIGALITH
	special 0x163

	setvar 0x8004 SPECIES_LILLIPUP
	special 0x163

	setvar 0x8004 SPECIES_HERDIER
	special 0x163

	setvar 0x8004 SPECIES_STOUTLAND
	special 0x163

	setvar 0x8004 SPECIES_CHINCHOU
	special 0x163

	setvar 0x8004 SPECIES_LANTURN
	special 0x163

	setvar 0x8004 SPECIES_RATTATA_A
	special 0x163

	setvar 0x8004 SPECIES_RATICATE_A
	special 0x163

	setvar 0x8004 SPECIES_FARFETCHD_G
	special 0x163

	setvar 0x8004 SPECIES_SIRFETCHD
	special 0x163

	setvar 0x8004 SPECIES_FLETCHLING
	special 0x163

	setvar 0x8004 SPECIES_FLETCHINDER
	special 0x163

	setvar 0x8004 SPECIES_TALONFLAME
	special 0x163

	setvar 0x8004 SPECIES_FLABEBE
	special 0x163

	setvar 0x8004 SPECIES_FLABEBE_BLUE
	special 0x163

	setvar 0x8004 SPECIES_FLABEBE_ORANGE
	special 0x163

	setvar 0x8004 SPECIES_FLABEBE_YELLOW
	special 0x163

	setvar 0x8004 SPECIES_FLABEBE_WHITE
	special 0x163

	setvar 0x8004 SPECIES_FLOETTE
	special 0x163

	setvar 0x8004 SPECIES_FLOETTE_BLUE
	special 0x163

	setvar 0x8004 SPECIES_FLOETTE_ORANGE
	special 0x163

	setvar 0x8004 SPECIES_FLOETTE_YELLOW
	special 0x163

	setvar 0x8004 SPECIES_FLOETTE_WHITE
	special 0x163

	setvar 0x8004 SPECIES_FLORGES
	special 0x163

	setvar 0x8004 SPECIES_FLORGES_BLUE
	special 0x163

	setvar 0x8004 SPECIES_FLORGES_ORANGE
	special 0x163

	setvar 0x8004 SPECIES_FLORGES_YELLOW
	special 0x163

	setvar 0x8004 SPECIES_FLORGES_WHITE
	special 0x163

	setvar 0x8004 SPECIES_CUTIEFLY
	special 0x163

	setvar 0x8004 SPECIES_RIBOMBEE
	special 0x163

	setvar 0x8004 SPECIES_RALTS
	special 0x163

	setvar 0x8004 SPECIES_KIRLIA
	special 0x163

	setvar 0x8004 SPECIES_GARDEVOIR
	special 0x163

	setvar 0x8004 SPECIES_GARDEVOIR_MEGA
	special 0x163

	setvar 0x8004 SPECIES_GALLADE
	special 0x163

	setvar 0x8004 SPECIES_GALLADE_MEGA
	special 0x163

	setvar 0x8004 SPECIES_FERROSEED
	special 0x163

	setvar 0x8004 SPECIES_FERROTHORN
	special 0x163

	setvar 0x8004 SPECIES_COMBEE
	special 0x163

	setvar 0x8004 SPECIES_VESPIQUEN
	special 0x163

	setvar 0x8004 SPECIES_SCRAGGY
	special 0x163

	setvar 0x8004 SPECIES_SCRAFTY
	special 0x163

	setvar 0x8004 SPECIES_CACNEA
	special 0x163

	setvar 0x8004 SPECIES_CACTURNE
	special 0x163

	setvar 0x8004 SPECIES_WINGULL
	special 0x163

	setvar 0x8004 SPECIES_PELIPPER
	special 0x163

	setvar 0x8004 SPECIES_HELIOPTILE
	special 0x163

	setvar 0x8004 SPECIES_HELIOLISK
	special 0x163

	setvar 0x8004 SPECIES_VULLABY
	special 0x163

	setvar 0x8004 SPECIES_MANDIBUZZ
	special 0x163

	setvar 0x8004 SPECIES_CASTFORM
	special 0x163

	setvar 0x8004 SPECIES_TRAPINCH
	special 0x163

	setvar 0x8004 SPECIES_VIBRAVA
	special 0x163

	setvar 0x8004 SPECIES_FLYGON
	special 0x163

	setvar 0x8004 SPECIES_SANDILE
	special 0x163

	setvar 0x8004 SPECIES_KROKOROK
	special 0x163

	setvar 0x8004 SPECIES_KROOKODILE
	special 0x163

	setvar 0x8004 SPECIES_HIPPOPOTAS
	special 0x163

	setvar 0x8004 SPECIES_HIPPOPOTAS_F
	special 0x163

	setvar 0x8004 SPECIES_HIPPOWDON
	special 0x163

	setvar 0x8004 SPECIES_HIPPOWDON_F
	special 0x163

	setvar 0x8004 SPECIES_CORPHISH
	special 0x163

	setvar 0x8004 SPECIES_CRAWDAUNT
	special 0x163

	setvar 0x8004 SPECIES_MAGIKARP
	special 0x163

	setvar 0x8004 SPECIES_GYARADOS
	special 0x163

	setvar 0x8004 SPECIES_GYARADOS_MEGA
	special 0x163

	setvar 0x8004 SPECIES_INKAY
	special 0x163

	setvar 0x8004 SPECIES_MALAMAR
	special 0x163

	setvar 0x8004 SPECIES_NINCADA
	special 0x163

	setvar 0x8004 SPECIES_NINJASK
	special 0x163

	setvar 0x8004 SPECIES_SHEDINJA
	special 0x163

	setvar 0x8004 SPECIES_WYNAUT
	special 0x163

	setvar 0x8004 SPECIES_WOBBUFFET
	special 0x163

	setvar 0x8004 SPECIES_CARBINK
	special 0x163

	setvar 0x8004 SPECIES_KLINK
	special 0x163

	setvar 0x8004 SPECIES_KLINKLANG
	special 0x163

	setvar 0x8004 SPECIES_KLANG
	special 0x163

	setvar 0x8004 SPECIES_KLINKLANG
	special 0x163

	setvar 0x8004 SPECIES_SABLEYE
	special 0x163

	setvar 0x8004 SPECIES_SABLEYE_MEGA
	special 0x163

	setvar 0x8004 SPECIES_MAWILE
	special 0x163

	setvar 0x8004 SPECIES_MAWILE_MEGA
	special 0x163

	setvar 0x8004 SPECIES_SHUCKLE
	special 0x163

	setvar 0x8004 SPECIES_JANGMO_O
	special 0x163

	setvar 0x8004 SPECIES_HAKAMO_O
	special 0x163

	setvar 0x8004 SPECIES_KOMMO_O
	special 0x163

	setvar 0x8004 SPECIES_CUBCHOO
	special 0x163

	setvar 0x8004 SPECIES_BEARTIC
	special 0x163

	setvar 0x8004 SPECIES_SWINUB
	special 0x163

	setvar 0x8004 SPECIES_PILOSWINE
	special 0x163

	setvar 0x8004 SPECIES_MAMOSWINE
	special 0x163

	setvar 0x8004 SPECIES_SNORUNT
	special 0x163

	setvar 0x8004 SPECIES_GLALIE
	special 0x163

	setvar 0x8004 SPECIES_GLALIE_MEGA
	special 0x163

	setvar 0x8004 SPECIES_FROSLASS
	special 0x163

	setvar 0x8004 SPECIES_NOIBAT
	special 0x163

	setvar 0x8004 SPECIES_NOIVERN
	special 0x163

	setvar 0x8004 SPECIES_TYRUNT
	special 0x163

	setvar 0x8004 SPECIES_TYRANTRUM
	special 0x163

	setvar 0x8004 SPECIES_SNEASEL
	special 0x163

	setvar 0x8004 SPECIES_WEAVILE
	special 0x163

	setvar 0x8004 SPECIES_SNOM
	special 0x163

	setvar 0x8004 SPECIES_FROSMOTH
	special 0x163

	setvar 0x8004 SPECIES_DARUMAKA_G
	special 0x163

	setvar 0x8004 SPECIES_DARMANITAN_G
	special 0x163

	setvar 0x8004 SPECIES_DARMANITAN_G_ZEN
	special 0x163

	setvar 0x8004 SPECIES_HOUNDOUR
	special 0x163

	setvar 0x8004 SPECIES_HOUNDOOM
	special 0x163

	setvar 0x8004 SPECIES_HOUNDOOM_MEGA
	special 0x163

	setvar 0x8004 SPECIES_LARVESTA
	special 0x163

	setvar 0x8004 SPECIES_VOLCARONA
	special 0x163

	setvar 0x8004 SPECIES_MINIOR_SHIELD
	special 0x163

	setvar 0x8004 SPECIES_ROLYCOLY
	special 0x163

	setvar 0x8004 SPECIES_CARKOL
	special 0x163

	setvar 0x8004 SPECIES_COALOSSAL
	special 0x163

	setvar 0x8004 SPECIES_SKARMORY
	special 0x163

	setvar 0x8004 SPECIES_SALANDIT
	special 0x163

	setvar 0x8004 SPECIES_SALAZZLE
	special 0x163

	setvar 0x8004 SPECIES_FRILLISH
	special 0x163

	setvar 0x8004 SPECIES_FRILLISH_F
	special 0x163

	setvar 0x8004 SPECIES_JELLICENT
	special 0x163

	setvar 0x8004 SPECIES_JELLICENT_F
	special 0x163

	setvar 0x8004 SPECIES_FOONGUS
	special 0x163

	setvar 0x8004 SPECIES_AMOONGUSS
	special 0x163

	setvar 0x8004 SPECIES_SHIELDON
	special 0x163

	setvar 0x8004 SPECIES_BASTIODON
	special 0x163

	setvar 0x8004 SPECIES_TIMBURR
	special 0x163

	setvar 0x8004 SPECIES_GURDURR
	special 0x163

	setvar 0x8004 SPECIES_CONKELDURR
	special 0x163

	setvar 0x8004 SPECIES_AMAURA
	special 0x163

	setvar 0x8004 SPECIES_AURORUS
	special 0x163

	setvar 0x8004 SPECIES_TURTONATOR
	special 0x163

	setvar 0x8004 SPECIES_MIME_JR_G
	special 0x163

	setvar 0x8004 SPECIES_MR_MIME_G
	special 0x163

	setvar 0x8004 SPECIES_MR_RIME
	special 0x163

	setvar 0x8004 SPECIES_SLUGMA
	special 0x163

	setvar 0x8004 SPECIES_MAGCARGO
	special 0x163

	setvar 0x8004 SPECIES_HATENNA
	special 0x163

	setvar 0x8004 SPECIES_HATTREM
	special 0x163

	setvar 0x8004 SPECIES_HATTERENE
	special 0x163

	setvar 0x8004 SPECIES_ORANGURU
	special 0x163

	setvar 0x8004 SPECIES_PASSIMIAN
	special 0x163

	setvar 0x8004 SPECIES_TORKOAL
	special 0x163

	setvar 0x8004 SPECIES_LILEEP
	special 0x163

	setvar 0x8004 SPECIES_CRADILY
	special 0x163

	setvar 0x8004 SPECIES_SHELLDER
	special 0x163

	setvar 0x8004 SPECIES_CLOYSTER
	special 0x163

	setvar 0x8004 SPECIES_SIZZLIPEDE
	special 0x163

	setvar 0x8004 SPECIES_CENTISKORCH
	special 0x163

	setvar 0x8004 SPECIES_COTTONEE
	special 0x163

	setvar 0x8004 SPECIES_WHIMSICOTT
	special 0x163

	setvar 0x8004 SPECIES_DITTO
	special 0x163

	setvar 0x8004 SPECIES_EEVEE
	special 0x163

	setvar 0x8004 SPECIES_VAPOREON
	special 0x163

	setvar 0x8004 SPECIES_JOLTEON
	special 0x163

	setvar 0x8004 SPECIES_FLAREON
	special 0x163

	setvar 0x8004 SPECIES_ESPEON
	special 0x163

	setvar 0x8004 SPECIES_UMBREON
	special 0x163

	setvar 0x8004 SPECIES_LEAFEON
	special 0x163

	setvar 0x8004 SPECIES_GLACEON
	special 0x163

	setvar 0x8004 SPECIES_SYLVEON
	special 0x163

	setvar 0x8004 SPECIES_MAREEP
	special 0x163

	setvar 0x8004 SPECIES_FLAAFFY
	special 0x163

	setvar 0x8004 SPECIES_AMPHAROS
	special 0x163

	setvar 0x8004 SPECIES_AMPHAROS_MEGA
	special 0x163

	setvar 0x8004 SPECIES_TOGEPI
	special 0x163

	setvar 0x8004 SPECIES_TOGETIC
	special 0x163

	setvar 0x8004 SPECIES_TOGEKISS
	special 0x163

	setvar 0x8004 SPECIES_MUDBRAY
	special 0x163

	setvar 0x8004 SPECIES_MUDSDALE
	special 0x163

	setvar 0x8004 SPECIES_HAPPINY
	special 0x163

	setvar 0x8004 SPECIES_CHANSEY
	special 0x163

	setvar 0x8004 SPECIES_BLISSEY
	special 0x163

	setvar 0x8004 SPECIES_MIENFOO
	special 0x163

	setvar 0x8004 SPECIES_MIENSHAO
	special 0x163

	setvar 0x8004 SPECIES_SKIDDO
	special 0x163

	setvar 0x8004 SPECIES_GOGOAT
	special 0x163

	setvar 0x8004 SPECIES_RIOLU
	special 0x163

	setvar 0x8004 SPECIES_LUCARIO
	special 0x163

	setvar 0x8004 SPECIES_LUCARIO_MEGA
	special 0x163

	setvar 0x8004 SPECIES_DRATINI
	special 0x163

	setvar 0x8004 SPECIES_DRAGONAIR
	special 0x163

	setvar 0x8004 SPECIES_DRAGONITE
	special 0x163

	setvar 0x8004 SPECIES_PACHIRISU
	special 0x163

	setvar 0x8004 SPECIES_ROTOM
	special 0x163

	setvar 0x8004 SPECIES_ROTOM_HEAT
	special 0x163

	setvar 0x8004 SPECIES_ROTOM_WASH
	special 0x163

	setvar 0x8004 SPECIES_ROTOM_FROST
	special 0x163

	setvar 0x8004 SPECIES_ROTOM_FAN
	special 0x163

	setvar 0x8004 SPECIES_ROTOM_MOW
	special 0x163

	setvar 0x8004 SPECIES_TOXEL
	special 0x163

	setvar 0x8004 SPECIES_TOXTRICITY
	special 0x163

	setvar 0x8004 SPECIES_TOXTRICITY_LOW_KEY
	special 0x163

	setvar 0x8004 SPECIES_HORSEA
	special 0x163

	setvar 0x8004 SPECIES_SEADRA
	special 0x163

	setvar 0x8004 SPECIES_KINGDRA
	special 0x163

	setvar 0x8004 SPECIES_CROAGUNK
	special 0x163

	setvar 0x8004 SPECIES_TOXICROAK
	special 0x163

	setvar 0x8004 SPECIES_GOOMY
	special 0x163

	setvar 0x8004 SPECIES_SLIGGOO
	special 0x163

	setvar 0x8004 SPECIES_GOODRA
	special 0x163

	setvar 0x8004 SPECIES_SHELLOS
	special 0x163

	setvar 0x8004 SPECIES_SHELLOS_EAST
	special 0x163

	setvar 0x8004 SPECIES_GASTRODON
	special 0x163

	setvar 0x8004 SPECIES_GASTRODON_EAST
	special 0x163

	setvar 0x8004 SPECIES_MIMIKYU
	special 0x163

	setvar 0x8004 SPECIES_MIMIKYU_BUSTED
	special 0x163

	setvar 0x8004 SPECIES_DUSKULL
	special 0x163

	setvar 0x8004 SPECIES_DUSCLOPS
	special 0x163

	setvar 0x8004 SPECIES_DUSKNOIR
	special 0x163

	setvar 0x8004 SPECIES_EMOLGA
	special 0x163

	setvar 0x8004 SPECIES_CARVANHA
	special 0x163

	setvar 0x8004 SPECIES_SHARPEDO
	special 0x163

	setvar 0x8004 SPECIES_SHARPEDO_MEGA
	special 0x163

	setvar 0x8004 SPECIES_HERACROSS
	special 0x163

	setvar 0x8004 SPECIES_HERACROSS_MEGA
	special 0x163

	setvar 0x8004 SPECIES_YAMASK
	special 0x163

	setvar 0x8004 SPECIES_YAMASK_G
	special 0x163

	setvar 0x8004 SPECIES_COFAGRIGUS
	special 0x163

	setvar 0x8004 SPECIES_RUNERIGUS
	special 0x163

	setvar 0x8004 SPECIES_DHELMISE
	special 0x163

	setvar 0x8004 SPECIES_PINCURCHIN
	special 0x163

	setvar 0x8004 SPECIES_MORPEKO
	special 0x163

	setvar 0x8004 SPECIES_MORPEKO_HANGRY
	special 0x163

	setvar 0x8004 SPECIES_STUNFISK_G
	special 0x163

	setvar 0x8004 SPECIES_MISDREAVUS
	special 0x163

	setvar 0x8004 SPECIES_MISMAGIUS
	special 0x163

	setvar 0x8004 SPECIES_GRIMER_A
	special 0x163

	setvar 0x8004 SPECIES_MUK_A
	special 0x163

	setvar 0x8004 SPECIES_GIBLE
	special 0x163

	setvar 0x8004 SPECIES_GABITE
	special 0x163

	setvar 0x8004 SPECIES_GARCHOMP
	special 0x163

	setvar 0x8004 SPECIES_GARCHOMP_MEGA
	special 0x163

	setvar 0x8004 SPECIES_BINACLE
	special 0x163

	setvar 0x8004 SPECIES_BARBARACLE
	special 0x163

	setvar 0x8004 SPECIES_MAREANIE
	special 0x163

	setvar 0x8004 SPECIES_TOXAPEX
	special 0x163

	setvar 0x8004 SPECIES_KOFFING
	special 0x163

	setvar 0x8004 SPECIES_KOFFING_G
	special 0x163

	setvar 0x8004 SPECIES_WEEZING
	special 0x163

	setvar 0x8004 SPECIES_WEEZING_G
	special 0x163

	setvar 0x8004 SPECIES_ZORUA
	special 0x163

	setvar 0x8004 SPECIES_ZOROARK
	special 0x163

	setvar 0x8004 SPECIES_LAPRAS
	special 0x163

	setvar 0x8004 SPECIES_CRABRAWLER
	special 0x163

	setvar 0x8004 SPECIES_CRABOMINABLE
	special 0x163

	setvar 0x8004 SPECIES_PHANTUMP
	special 0x163

	setvar 0x8004 SPECIES_TREVENANT
	special 0x163

	setvar 0x8004 SPECIES_SANDYGAST
	special 0x163

	setvar 0x8004 SPECIES_PALOSSAND
	special 0x163

	setvar 0x8004 SPECIES_SLOWPOKE
	special 0x163

	setvar 0x8004 SPECIES_SLOWBRO
	special 0x163

	setvar 0x8004 SPECIES_SLOWBRO_MEGA
	special 0x163

	setvar 0x8004 SPECIES_SLOWKING
	special 0x163

	setvar 0x8004 SPECIES_CORSOLA_G
	special 0x163

	setvar 0x8004 SPECIES_CURSOLA
	special 0x163

	setvar 0x8004 SPECIES_FALINKS
	special 0x163

	setvar 0x8004 SPECIES_PAWNIARD
	special 0x163

	setvar 0x8004 SPECIES_BISHARP
	special 0x163

	setvar 0x8004 SPECIES_ELGYEM
	special 0x163

	setvar 0x8004 SPECIES_BEHEEYEM
	special 0x163

	setvar 0x8004 SPECIES_MANKEY
	special 0x163

	setvar 0x8004 SPECIES_PRIMEAPE
	special 0x163

	setvar 0x8004 SPECIES_BERGMITE
	special 0x163

	setvar 0x8004 SPECIES_AVALUGG
	special 0x163

	setvar 0x8004 SPECIES_STONJOURNER
	special 0x163

	setvar 0x8004 SPECIES_DELIBIRD
	special 0x163

	setvar 0x8004 SPECIES_COMFEY
	special 0x163

	setvar 0x8004 SPECIES_CUFANT
	special 0x163

	setvar 0x8004 SPECIES_COPPERAJAH
	special 0x163

	setvar 0x8004 SPECIES_JOLTIK
	special 0x163

	setvar 0x8004 SPECIES_GALVANTULA
	special 0x163

	setvar 0x8004 SPECIES_CARNIVINE
	special 0x163

	setvar 0x8004 SPECIES_LITLEO
	special 0x163

	setvar 0x8004 SPECIES_PYROAR
	special 0x163

	setvar 0x8004 SPECIES_PYROAR_FEMALE
	special 0x163

	setvar 0x8004 SPECIES_KANGASKHAN
	special 0x163

	setvar 0x8004 SPECIES_KANGASKHAN_MEGA
	special 0x163

	setvar 0x8004 SPECIES_DURALUDON
	special 0x163

	setvar 0x8004 SPECIES_ARTICUNO_G
	special 0x163

	setvar 0x8004 SPECIES_ZAPDOS_G
	special 0x163

	setvar 0x8004 SPECIES_MOLTRES_G
	special 0x163

	setvar 0x8004 SPECIES_JIRACHI
	special 0x163

	setvar 0x8004 SPECIES_SHAYMIN
	special 0x163

	setvar 0x8004 SPECIES_SHAYMIN_SKY
	special 0x163

	setvar 0x8004 SPECIES_KYOGRE
	special 0x163

	setvar 0x8004 SPECIES_KYOGRE_PRIMAL
	special 0x163

	setvar 0x8004 SPECIES_GROUDON
	special 0x163

	setvar 0x8004 SPECIES_GROUDON_PRIMAL
	special 0x163

	setvar 0x8004 SPECIES_VOLCANION
	special 0x163

	setvar 0x8004 SPECIES_ZARUDE
	special 0x163

	setvar 0x8004 SPECIES_ZARUDE_DADA
	special 0x163

	setvar 0x8004 SPECIES_GLASTRIER
	special 0x163

	setvar 0x8004 SPECIES_MELTAN
	special 0x163

	setvar 0x8004 SPECIES_MELMETAL
	special 0x163

	setvar 0x8004 SPECIES_VICTINI
	special 0x163

	setvar 0x8004 SPECIES_BULBASAUR
	special 0x163

	setvar 0x8004 SPECIES_IVYSAUR
	special 0x163

	setvar 0x8004 SPECIES_VENUSAUR
	special 0x163

	setvar 0x8004 SPECIES_VENUSAUR_MEGA
	special 0x163

	setvar 0x8004 SPECIES_CHARMANDER
	special 0x163

	setvar 0x8004 SPECIES_CHARMELEON
	special 0x163

	setvar 0x8004 SPECIES_CHARIZARD
	special 0x163

	setvar 0x8004 SPECIES_CHARIZARD_MEGA_X
	special 0x163

	setvar 0x8004 SPECIES_CHARIZARD_MEGA_Y
	special 0x163

	setvar 0x8004 SPECIES_SQUIRTLE
	special 0x163

	setvar 0x8004 SPECIES_WARTORTLE
	special 0x163

	setvar 0x8004 SPECIES_BLASTOISE
	special 0x163

	setvar 0x8004 SPECIES_BLASTOISE_MEGA
	special 0x163

	setvar 0x8004 SPECIES_CHIKORITA
	special 0x163

	setvar 0x8004 SPECIES_BAYLEEF
	special 0x163

	setvar 0x8004 SPECIES_MEGANIUM
	special 0x163

	setvar 0x8004 SPECIES_CYNDAQUIL
	special 0x163

	setvar 0x8004 SPECIES_QUILAVA
	special 0x163

	setvar 0x8004 SPECIES_TYPHLOSION
	special 0x163

	setvar 0x8004 SPECIES_TOTODILE
	special 0x163

	setvar 0x8004 SPECIES_CROCONAW
	special 0x163

	setvar 0x8004 SPECIES_FERALIGATR
	special 0x163

	setvar 0x8004 SPECIES_TREECKO
	special 0x163

	setvar 0x8004 SPECIES_GROVYLE
	special 0x163

	setvar 0x8004 SPECIES_SCEPTILE
	special 0x163

	setvar 0x8004 SPECIES_SCEPTILE_MEGA
	special 0x163

	setvar 0x8004 SPECIES_TORCHIC
	special 0x163

	setvar 0x8004 SPECIES_COMBUSKEN
	special 0x163

	setvar 0x8004 SPECIES_BLAZIKEN
	special 0x163

	setvar 0x8004 SPECIES_BLAZIKEN_MEGA
	special 0x163

	setvar 0x8004 SPECIES_MUDKIP
	special 0x163

	setvar 0x8004 SPECIES_MARSHTOMP
	special 0x163

	setvar 0x8004 SPECIES_SWAMPERT
	special 0x163

	setvar 0x8004 SPECIES_SWAMPERT_MEGA
	special 0x163

	setvar 0x8004 SPECIES_TURTWIG
	special 0x163

	setvar 0x8004 SPECIES_GROTLE
	special 0x163

	setvar 0x8004 SPECIES_TORTERRA
	special 0x163

	setvar 0x8004 SPECIES_CHIMCHAR
	special 0x163

	setvar 0x8004 SPECIES_MONFERNO
	special 0x163

	setvar 0x8004 SPECIES_INFERNAPE
	special 0x163

	setvar 0x8004 SPECIES_PIPLUP
	special 0x163

	setvar 0x8004 SPECIES_PRINPLUP
	special 0x163

	setvar 0x8004 SPECIES_EMPOLEON
	special 0x163

	setvar 0x8004 SPECIES_SNIVY
	special 0x163

	setvar 0x8004 SPECIES_SERVINE
	special 0x163

	setvar 0x8004 SPECIES_SERPERIOR
	special 0x163

	setvar 0x8004 SPECIES_TEPIG
	special 0x163

	setvar 0x8004 SPECIES_PIGNITE
	special 0x163

	setvar 0x8004 SPECIES_EMBOAR
	special 0x163

	setvar 0x8004 SPECIES_OSHAWOTT
	special 0x163

	setvar 0x8004 SPECIES_DEWOTT
	special 0x163

	setvar 0x8004 SPECIES_SAMUROTT
	special 0x163

	setvar 0x8004 SPECIES_CHESPIN
	special 0x163

	setvar 0x8004 SPECIES_QUILLADIN
	special 0x163

	setvar 0x8004 SPECIES_CHESNAUGHT
	special 0x163

	setvar 0x8004 SPECIES_FENNEKIN
	special 0x163

	setvar 0x8004 SPECIES_BRAIXEN
	special 0x163

	setvar 0x8004 SPECIES_DELPHOX
	special 0x163

	setvar 0x8004 SPECIES_FROAKIE
	special 0x163

	setvar 0x8004 SPECIES_FROGADIER
	special 0x163

	setvar 0x8004 SPECIES_GRENINJA
	special 0x163

	setvar 0x8004 SPECIES_ROWLET
	special 0x163

	setvar 0x8004 SPECIES_DARTRIX
	special 0x163

	setvar 0x8004 SPECIES_DECIDUEYE
	special 0x163

	setvar 0x8004 SPECIES_LITTEN
	special 0x163

	setvar 0x8004 SPECIES_TORRACAT
	special 0x163

	setvar 0x8004 SPECIES_INCINEROAR
	special 0x163

	setvar 0x8004 SPECIES_POPPLIO
	special 0x163

	setvar 0x8004 SPECIES_BRIONNE
	special 0x163

	setvar 0x8004 SPECIES_PRIMARINA
	special 0x163

	setvar 0x8004 SPECIES_GROOKEY
	special 0x163

	setvar 0x8004 SPECIES_THWACKEY
	special 0x163

	setvar 0x8004 SPECIES_RILLABOOM
	special 0x163

	setvar 0x8004 SPECIES_SCORBUNNY
	special 0x163

	setvar 0x8004 SPECIES_RABOOT
	special 0x163

	setvar 0x8004 SPECIES_CINDERACE
	special 0x163

	setvar 0x8004 SPECIES_SOBBLE
	special 0x163

	setvar 0x8004 SPECIES_DRIZZILE
	special 0x163

	setvar 0x8004 SPECIES_INTELEON
	special 0x163

	setvar 0x8004 SPECIES_COSMOG
	special 0x163

	setvar 0x8004 SPECIES_COSMOEM
	special 0x163

	setvar 0x8004 SPECIES_SOLGALEO
	special 0x163

	setvar 0x8004 SPECIES_LUNALA
	special 0x163

	setvar 0x8004 SPECIES_NIHILEGO
	special 0x163

	setvar 0x8004 SPECIES_BUZZWOLE
	special 0x163

	setvar 0x8004 SPECIES_PHEROMOSA
	special 0x163

	setvar 0x8004 SPECIES_XURKITREE
	special 0x163

	setvar 0x8004 SPECIES_CELESTEELA
	special 0x163

	setvar 0x8004 SPECIES_KARTANA
	special 0x163

	setvar 0x8004 SPECIES_GUZZLORD
	special 0x163

	setvar 0x8004 SPECIES_NECROZMA
	special 0x163

	setvar 0x8004 SPECIES_NECROZMA_DUSK_MANE
	special 0x163

	setvar 0x8004 SPECIES_NECROZMA_DAWN_WINGS
	special 0x163

	setvar 0x8004 SPECIES_NECROZMA_ULTRA
	special 0x163

	setvar 0x8004 SPECIES_POIPOLE
	special 0x163

	setvar 0x8004 SPECIES_NAGANADEL
	special 0x163

	setvar 0x8004 SPECIES_STAKATAKA
	special 0x163

	setvar 0x8004 SPECIES_BLACEPHALON
	special 0x163

	@ Give the player certain key items, like mega/primal reversion/ultra burst items
	setflag 0x828 @ Enable Pokemon Menu
	setflag 0x829 @ Enable Pokedex Menu
	additem ITEM_POKE_BALL 0x32 @ Give 50 pokeballs
	additem ITEM_RARE_CANDY 0x1E @ Give 30 rare candies
	additem ITEM_TOWN_MAP 0x1 @ Give town map
	@ giveitem2 0x169 0x1 0x13E @ Give town map with fanfare (base game uses both)
	additem ITEM_HM01 0x1 @ Cut
	additem ITEM_HM02 0x1 @ Fly
	additem ITEM_HM03 0x1 @ Surf
	additem ITEM_HM04 0x1 @ Strength
	additem ITEM_HM05 0x1 @ Rock Smash
	setflag 0x820 @ Badge 1, Field Badge
	setflag 0x821 @ Badge 2, Patch Badge
	setflag 0x822 @ Badge 3, Stormcloud Badge
	setflag 0x823 @ Badge 4, Roundabout Badge
	setflag 0x824 @ Badge 5, Tactician Badge
	setflag 0x825 @ Badge 6, Talent Badge
	setflag 0x826 @ Badge 7, Support Badge
	setflag 0x827 @ Badge 8, Double Badge

