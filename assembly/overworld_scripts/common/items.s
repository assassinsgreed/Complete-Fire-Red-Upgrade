.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global ItemScript_Common_FindTM
ItemScript_Common_FindTM:
    @ Expects variable CHOSEN_ITEM to be set to the Item ID
    finditem CHOSEN_ITEM 0x1
    return

.global ItemScript_Common_RareCandy
ItemScript_Common_RareCandy:
    finditem ITEM_RARE_CANDY 0x1
    end

.global ItemScript_Common_Potion
ItemScript_Common_Potion:
    finditem ITEM_POTION 0x1
    end

.global ItemScript_Common_SuperPotion
ItemScript_Common_SuperPotion:
    finditem ITEM_SUPER_POTION 0x1
    end

.global ItemScript_Common_HyperPotion
ItemScript_Common_HyperPotion:
    finditem ITEM_HYPER_POTION 0x1
    end

.global ItemScript_Common_Revive
ItemScript_Common_Revive:
    finditem ITEM_REVIVE 0x1
    end

.global ItemScript_Common_MaxRevive
ItemScript_Common_MaxRevive:
    finditem ITEM_MAX_REVIVE 0x1
    end

.global ItemScript_Common_Antidote
ItemScript_Common_Antidote:
    finditem ITEM_ANTIDOTE 0x1
    end

.global ItemScript_Common_FullHeal
ItemScript_Common_FullHeal:
    finditem ITEM_FULL_HEAL 0x1
    end

.global ItemScript_Common_FullRestore
ItemScript_Common_FullRestore:
    finditem ITEM_FULL_RESTORE 0x1
    end

.global ItemScript_Common_FreshWater
ItemScript_Common_FreshWater:
    finditem ITEM_FRESH_WATER 0x1
    end

.global ItemScript_Common_SodaPop
ItemScript_Common_SodaPop:
    finditem ITEM_SODA_POP 0x1
    end

.global ItemScript_Common_Elixir
ItemScript_Common_Elixir:
    finditem ITEM_ELIXIR 0x1
    end

.global ItemScript_Common_MaxElixir
ItemScript_Common_MaxElixir:
    finditem ITEM_MAX_ELIXIR 0x1
    end

.global ItemScript_Common_Repel
ItemScript_Common_Repel:
    finditem ITEM_REPEL 0x1
    end

.global ItemScript_Common_SuperRepel
ItemScript_Common_SuperRepel:
    finditem ITEM_SUPER_REPEL 0x1
    end

.global ItemScript_Common_MaxRepel
ItemScript_Common_MaxRepel:
    finditem ITEM_MAX_REPEL 0x1
    end

.global ItemScript_Common_PokeDoll
ItemScript_Common_PokeDoll:
    finditem ITEM_POKE_DOLL 0x1
    end

.global ItemScript_Common_EscapeRope
ItemScript_Common_EscapeRope:
    finditem ITEM_ESCAPE_ROPE 0x1
    end

.global ItemScript_Common_TinyMushroom
ItemScript_Common_TinyMushroom:
    finditem ITEM_TINY_MUSHROOM 0x1
    end

.global ItemScript_Common_StarPiece
ItemScript_Common_StarPiece:
    finditem ITEM_STAR_PIECE 0x1
    end

.global ItemScript_Common_Nugget
ItemScript_Common_Nugget:
    finditem ITEM_NUGGET 0x1
    end

.global ItemScript_Common_FireStone
ItemScript_Common_FireStone:
    finditem ITEM_FIRE_STONE 0x1
    end

.global ItemScript_Common_ThunderStone
ItemScript_Common_ThunderStone:
    finditem ITEM_THUNDER_STONE 0x1
    end

.global ItemScript_Common_LeafStone
ItemScript_Common_LeafStone:
    finditem ITEM_LEAF_STONE 0x1
    end

.global ItemScript_Common_SunStone
ItemScript_Common_SunStone:
    finditem ITEM_SUN_STONE 0x1
    end

.global ItemScript_Common_IceStone
ItemScript_Common_IceStone:
    finditem ITEM_ICE_STONE 0x1
    end

.global ItemScript_Common_DuskStone
ItemScript_Common_DuskStone:
    finditem ITEM_DUSK_STONE 0x1
    end

.global ItemScript_Common_LinkCord
ItemScript_Common_LinkCord:
    // CFRU labels this as Link Stone, but we call it Link Cord to align with Pokemon Legends Arceus
    finditem ITEM_LINK_STONE 0x1
    end

.global ItemScript_Common_ReaperCloth
ItemScript_Common_ReaperCloth:
    finditem ITEM_REAPER_CLOTH 0x1
    end

.global ItemScript_Common_CleanseTag
ItemScript_Common_CleanseTag:
    finditem ITEM_CLEANSE_TAG 0x1
    end

.global ItemScript_Common_SmoothRock
ItemScript_Common_SmoothRock:
    finditem ITEM_SMOOTH_ROCK 0x1
    end

.global ItemScript_Common_DampRock
ItemScript_Common_DampRock:
    finditem ITEM_DAMP_ROCK 0x1
    end

.global ItemScript_Common_HeatRock
ItemScript_Common_HeatRock:
    finditem ITEM_HEAT_ROCK 0x1
    end

.global ItemScript_Common_IcyRock
ItemScript_Common_IcyRock:
    finditem ITEM_ICY_ROCK 0x1
    end

.global ItemScript_Common_Snowball
ItemScript_Common_Snowball:
    finditem ITEM_SNOWBALL 0x1
    end

.global ItemScript_Common_AbsorbBulb
ItemScript_Common_AbsorbBulb:
    finditem ITEM_ABSORB_BULB 0x1
    end

.global ItemScript_Common_CellBattery
ItemScript_Common_CellBattery:
    finditem ITEM_CELL_BATTERY 0x1
    end

.global ItemScript_Common_MiracleSeed
ItemScript_Common_MiracleSeed:
    finditem ITEM_MIRACLE_SEED 0x1
    end

.global ItemScript_Common_MysticWater
ItemScript_Common_MysticWater:
    finditem ITEM_MYSTIC_WATER 0x1
    end

.global ItemScript_Common_HardStone
ItemScript_Common_HardStone:
    finditem ITEM_HARD_STONE 0x1
    end

.global ItemScript_Common_Magnet
ItemScript_Common_Magnet:
    finditem ITEM_MAGNET 0x1
    end

.global ItemScript_Common_SharpBeak
ItemScript_Common_SharpBeak:
    finditem ITEM_SHARP_BEAK 0x1
    end

.global ItemScript_Common_SoftSand
ItemScript_Common_SoftSand:
    finditem ITEM_SOFT_SAND 0x1
    end

.global ItemScript_Common_SilverPowder
ItemScript_Common_SilverPowder:
    finditem ITEM_SILVER_POWDER 0x1
    end

.global ItemScript_Common_BlackBelt
ItemScript_Common_BlackBelt:
    finditem ITEM_BLACK_BELT 0x1
    end

.global ItemScript_Common_BlackGlasses
ItemScript_Common_BlackGlasses:
    finditem ITEM_BLACK_GLASSES 0x1
    end

.global ItemScript_Common_NeverMeltIce
ItemScript_Common_NeverMeltIce:
    finditem ITEM_NEVER_MELT_ICE 0x1
    end

.global ItemScript_Common_PoisonBarb
ItemScript_Common_PoisonBarb:
    finditem ITEM_POISON_BARB 0x1
    end

.global ItemScript_Common_SpellTag
ItemScript_Common_SpellTag:
    finditem ITEM_SPELL_TAG 0x1
    end

.global ItemScript_Common_DestinyKnot
ItemScript_Common_DestinyKnot:
    finditem ITEM_DESTINY_KNOT 0x1
    end

.global ItemScript_Common_QuickClaw
ItemScript_Common_QuickClaw:
    finditem ITEM_QUICK_CLAW 0x1
    end

.global ItemScript_Common_FocusSash
ItemScript_Common_FocusSash:
    finditem ITEM_FOCUS_SASH 0x1
    end

.global ItemScript_Common_ChoiceBand
ItemScript_Common_ChoiceBand:
    finditem ITEM_CHOICE_BAND 0x1
    end

.global ItemScript_Common_ChoiceScarf
ItemScript_Common_ChoiceScarf:
    finditem ITEM_CHOICE_SCARF 0x1
    end

.global ItemScript_Common_Stick
ItemScript_Common_Stick:
    finditem ITEM_STICK 0x1
    end

.global ItemScript_Common_MetalPowder
ItemScript_Common_MetalPowder:
    finditem ITEM_METAL_POWDER 0x1
    end

.global ItemScript_Common_LaxIncense
ItemScript_Common_LaxIncense:
    finditem ITEM_LAX_INCENSE 0x1
    end

.global ItemScript_Common_RoseIncense
ItemScript_Common_RoseIncense:
    finditem ITEM_ROSE_INCENSE 0x1
    end

.global ItemScript_Common_OddIncense
ItemScript_Common_OddIncense:
    finditem ITEM_ODD_INCENSE 0x1
    end

.global ItemScript_Common_RockIncense
ItemScript_Common_RockIncense:
    finditem ITEM_ROCK_INCENSE 0x1
    end

.global ItemScript_Common_MetalCoat
ItemScript_Common_MetalCoat:
    finditem ITEM_METAL_COAT 0x1
    end

.global ItemScript_Common_DireHit
ItemScript_Common_DireHit:
    finditem ITEM_DIRE_HIT 0x1
    end

.global ItemScript_Common_HpUp
ItemScript_Common_HpUp:
    finditem ITEM_HP_UP 0x1
    end

.global ItemScript_Common_Protein
ItemScript_Common_Protein:
    finditem ITEM_PROTEIN 0x1
    end

.global ItemScript_Common_Iron
ItemScript_Common_Iron:
    finditem ITEM_IRON 0x1
    end

.global ItemScript_Common_Carbos
ItemScript_Common_Carbos:
    finditem ITEM_CARBOS 0x1
    end

.global ItemScript_Common_Calcium
ItemScript_Common_Calcium:
    finditem ITEM_CALCIUM 0x1
    end

.global ItemScript_Common_Zinc
ItemScript_Common_Zinc:
    finditem ITEM_ZINC 0x1
    end

.global ItemScript_Common_Pokeball
ItemScript_Common_Pokeball:
    finditem ITEM_POKE_BALL 0x1
    end

.global ItemScript_Common_Greatball
ItemScript_Common_Greatball:
    finditem ITEM_GREAT_BALL 0x1
    end

.global ItemScript_Common_Ultraball
ItemScript_Common_Ultraball:
    finditem ITEM_ULTRA_BALL 0x1
    end

.global ItemScript_Common_Masterball
ItemScript_Common_Masterball:
    finditem ITEM_MASTER_BALL 0x1
    end

.global ItemScript_Common_Healball
ItemScript_Common_Healball:
    finditem ITEM_HEAL_BALL 0x1
    end

.global ItemScript_Common_Nestball
ItemScript_Common_Nestball:
    finditem ITEM_NEST_BALL 0x1
    end

.global ItemScript_Common_GrassySeed
ItemScript_Common_GrassySeed:
    finditem ITEM_GRASSY_SEED 0x1
    end

.global ItemScript_Common_ElectricSeed
ItemScript_Common_ElectricSeed:
    finditem ITEM_ELECTRIC_SEED 0x1
    end

.global ItemScript_Common_MistySeed
ItemScript_Common_MistySeed:
    finditem ITEM_MISTY_SEED 0x1
    end

.global ItemScript_Common_PsychicSeed
ItemScript_Common_PsychicSeed:
    finditem ITEM_PSYCHIC_SEED 0x1
    end

.global ItemScript_Common_TerrainExtender
ItemScript_Common_TerrainExtender:
    finditem ITEM_TERRAIN_EXTENDER 0x1
    end

.global ItemScript_Common_HeavyDutyBoots
ItemScript_Common_HeavyDutyBoots:
    finditem ITEM_HEAVY_DUTY_BOOTS 0x1
    end

.global ItemScript_Common_RedCard
ItemScript_Common_RedCard:
    finditem ITEM_RED_CARD 0x1
    end

.global ItemScript_Common_RazorClaw
ItemScript_Common_RazorClaw:
    finditem ITEM_RAZOR_CLAW 0x1
    end

.global ItemScript_Common_EjectButton
ItemScript_Common_EjectButton:
    finditem ITEM_EJECT_BUTTON 0x1
    end

.global ItemScript_Common_ShellBell
ItemScript_Common_ShellBell:
    finditem ITEM_SHELL_BELL 0x1
    end

.global ItemScript_Common_KingsRock
ItemScript_Common_KingsRock:
    finditem ITEM_KINGS_ROCK 0x1
    end

.global ItemScript_Common_LaggingTail
ItemScript_Common_LaggingTail:
    finditem ITEM_LAGGING_TAIL 0x1
    end

.global ItemScript_Common_DragonScale
ItemScript_Common_DragonScale:
    finditem ITEM_DRAGON_SCALE 0x1
    end

.global ItemScript_Common_BlackSludge
ItemScript_Common_BlackSludge:
    finditem ITEM_BLACK_SLUDGE 0x1
    end
