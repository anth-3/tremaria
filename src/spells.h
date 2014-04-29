/***************************************************************************************************
*                                                                   Part of the Realms of Tremaria *
* File: spells.h                                                                A CircleMUD/tbaMUD *
* Description: Constants and function prototypes for the spell system.                             *
*                                                                                                  *
* All rights reserved.  See license for complete information.                                      *
*                                                                                                  *
* Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University                           *
* CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.                                         *
* Last updated: 28 April 2014 -- anth*3                                                            *
***************************************************************************************************/

#ifndef __SPELLS_H__
#define __SPELLS_H__

#define DEFAULT_STAFF_LVL	12
#define DEFAULT_WAND_LVL	12

#define CAST_UNDEFINED	(-1)
#define CAST_SPELL		0
#define CAST_POTION		1
#define CAST_WAND		2
#define CAST_STAFF		3
#define CAST_SCROLL		4
#define CAST_BREATH		5

#define MAG_DAMAGE		(1 << 0)
#define MAG_AFFECTS		(1 << 1)
#define MAG_UNAFFECTS	(1 << 2)
#define MAG_POINTS		(1 << 3)
#define MAG_ALTER_OBJS	(1 << 4)
#define MAG_GROUPS		(1 << 5)
#define MAG_MASSES		(1 << 6)
#define MAG_AREAS		(1 << 7)
#define MAG_SUMMONS		(1 << 8)
#define MAG_CREATIONS	(1 << 9)
#define MAG_MANUAL		(1 << 10)
#define MAG_ROOMS		(1 << 11)

#define TYPE_UNDEFINED				(-1)
#define SPELL_RESERVED_DBC			0  /* SKILL NUMBER ZERO -- RESERVED */

/* PLAYER SPELLS -- Numbered from 1 to MAX_SPELLS */

#define SPELL_ARMOR							   1 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_TELEPORT						   2 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_BLESS							   3 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_BLINDNESS						   4 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_BURNING_HANDS					   5 /* Reserved Skill[] DO NOT CHANGE */ /* offensive */
#define SPELL_CALL_LIGHTNING				   6 /* Reserved Skill[] DO NOT CHANGE */ /* offensive */
#define SPELL_CHARM							   7 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_CHILL_TOUCH					   8 /* Reserved Skill[] DO NOT CHANGE */ /* offensive */
#define SPELL_CLONE							   9 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_COLOR_SPRAY					  10 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_CONTROL_WEATHER				  11 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_CREATE_FOOD					  12 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_CREATE_WATER					  13 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_CURE_BLIND					  14 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_CURE_CRITIC					  15 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_CURE_LIGHT					  16 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_CURSE							  17 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_DETECT_ALIGN					  18 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_DETECT_INVIS					  19 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_DETECT_MAGIC					  20 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_DETECT_POISON					  21 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_DISPEL_EVIL					  22 /* Reserved Skill[] DO NOT CHANGE */ /* offensive */
#define SPELL_EARTHQUAKE					  23 /* Reserved Skill[] DO NOT CHANGE */ /* offensive */
#define SPELL_ENCHANT_WEAPON				  24 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_ENERGY_DRAIN					  25 /* Reserved Skill[] DO NOT CHANGE */ /* offensive */
#define SPELL_FIREBALL						  26 /* Reserved Skill[] DO NOT CHANGE */ /* offensive */
#define SPELL_HARM							  27 /* Reserved Skill[] DO NOT CHANGE */ /* offensive */
#define SPELL_HEAL							  28 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_INVISIBLE						  29 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_LIGHTNING_BOLT				  30 /* Reserved Skill[] DO NOT CHANGE */ /* offensive */
#define SPELL_LOCATE_OBJECT					  31 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_MAGIC_MISSILE					  32 /* Reserved Skill[] DO NOT CHANGE */ /* offensive */
#define SPELL_POISON						  33 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_PROT_FROM_EVIL				  34 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_REMOVE_CURSE					  35 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_SANCTUARY						  36 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_SHOCKING_GRASP				  37 /* Reserved Skill[] DO NOT CHANGE */ /* offensive */
#define SPELL_SLEEP							  38 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_STRENGTH						  39 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_SUMMON						  40 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_VENTRILOQUATE					  41 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_WORD_OF_RECALL				  42 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_REMOVE_POISON					  43 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_SENSE_LIFE					  44 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_ANIMATE_DEAD					  45 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_DISPEL_GOOD					  46 /* Reserved Skill[] DO NOT CHANGE */ /* offensive */
#define SPELL_GROUP_ARMOR					  47 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_GROUP_HEAL					  48 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_GROUP_RECALL					  49 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_INFRAVISION					  50 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_WATERWALK						  51 /* Reserved Skill[] DO NOT CHANGE */
#define SPELL_FLY							  52
#define SPELL_RELOCATE						  53
#define SPELL_FEAR							  54
#define SPELL_PORTAL						  55
#define SPELL_RECHARGE						  56
#define SPELL_ACID_ARROW					  57  /* offensive */
#define SPELL_ACID_BLAST					  58  /* offensive */
#define SPELL_ACID_BOLT						  59  /* offensive */
#define SPELL_ACID_CLOUD					  60  /* offensive */
#define SPELL_ACID_HANDS					  61  /* offensive */
#define SPELL_ACID_POOL						  62  /* offensive */
#define SPELL_ACIDBALL						  63  /* offensive */
#define SPELL_AID							  64
#define SPELL_ANIMAL_AFFINITY				  65
#define SPELL_ANIMAL_SUMMONING_I			  66
#define SPELL_ANIMAL_SUMMONING_II			  67
#define SPELL_ANIMAL_SUMMONING_III			  68
#define SPELL_ANIMATE_TREE					  69
#define SPELL_BARKSKIN						  70
#define SPELL_BETRAY						  71
#define SPELL_BLACK_STORM					  72  /* offensive */
#define SPELL_BLADE_BARRIER					  73  /* offensive */
#define SPELL_BLINK				 			  74
#define SPELL_BLOODLUST						  75
#define SPELL_BLOODSTAR						  76  /* offensive */
#define SPELL_BREATHE_WATER					  77
#define SPELL_CANTRIP						  78
#define SPELL_CAUSE_CRIT					  79  /* offensive */
#define SPELL_CAUSE_LIGHT					  80  /* offensive */
#define SPELL_CAUSE_SERIOUS					  81  /* offensive */
#define SPELL_CHARM_ANIMAL					  82
#define SPELL_CHARM_DANCE					  83
#define SPELL_CHARM_MONSTER					  84
#define SPELL_CHARM_PERSON					  85
#define SPELL_CHARM_UNDEAD					  86
#define SPELL_COLD_SNAP						  87  /* offensive */
#define SPELL_COMET_STRIKE					  88  /* offensive */
#define SPELL_COMMAND_UNDEAD				  89
#define SPELL_COMPREHEND_LANG				  90
#define SPELL_CONE_OF_ACID					  91  /* offensive */
#define SPELL_CONE_OF_COLD					  92  /* offensive */
#define SPELL_CONE_OF_FIRE					  93  /* offensive */
#define SPELL_CONJURE_AIR_ELEM				  94
#define SPELL_CONJURE_EARTH_ELEM			  95
#define SPELL_CONJURE_FIRE_ELEM				  96
#define SPELL_CONJURE_WATER_ELEM			  97
#define SPELL_CONTINUAL_LIGHT				  98
#define SPELL_CURE_DISEASE					  99
#define SPELL_CURE_SERIOUS					 100
#define SPELL_DARKNESS						 101
#define SPELL_DEADLY_POISON_I				 102
#define SPELL_DEADLY_POISON_II				 103
#define SPELL_DEADLY_POISON_III				 104
#define SPELL_DEATH_DANCE					 105
#define SPELL_DEATH_FOG						 106  /* offensive */
#define SPELL_DISINTEGRATE					 107  /* offensive */
#define SPELL_DISPEL_MAGIC					 108
#define SPELL_DRAGONS_BREATH				 109  /* offensive */
#define SPELL_DRAIN_LIFE					 110  /* offensive */
#define SPELL_EMPOWER						 111
#define SPELL_ENCHANT_ARMOR					 112
#define SPELL_ENGAGE						 113
#define SPELL_ENLARGE						 114
#define SPELL_ENTANGLE						 115
#define SPELL_FAIRY_FIRE					 116
#define SPELL_FAIRY_FOG						 117
#define SPELL_FIERY_CONSTRICTOR				 118
#define SPELL_FIRE_SEEDS					 119  /* offensive */
#define SPELL_FIRE_STORM					 120  /* offensive */
#define SPELL_FLAME_ARROW					 121  /* offensive */
#define SPELL_FLAME_BLADE					 122
#define SPELL_FLAME_STRIKE					 123  /* offensive */
#define SPELL_FOG_CLOUD						 124
#define SPELL_FOG_WARRIOR					 125
#define SPELL_FORCE_BOLT					 126  /* offensive */
#define SPELL_FREEZING_SPHERE				 127  /* offensive */
#define SPELL_FROST_HANDS					 128  /* offensive */
#define SPELL_GATE							 129
#define SPELL_GROUP_BREATHE_WATER			 130
#define SPELL_GROUP_CURE_CRIT				 131
#define SPELL_GROUP_PROT_DRAGON_FEAR		 132
#define SPELL_GROUP_PROT_FROM_ACID			 133
#define SPELL_GROUP_PROT_FROM_COLD			 134
#define SPELL_GROUP_PROT_FROM_ELEC			 135
#define SPELL_GROUP_PROT_FROM_EVIL			 136
#define SPELL_GROUP_PROT_FROM_FEAR			 137
#define SPELL_GROUP_PROT_FROM_FIRE			 138
#define SPELL_GROUP_PROT_FROM_GAS			 139
#define SPELL_GROUP_PROT_FROM_GOOD			 140
#define SPELL_GROUP_PROT_FROM_UNDEAD		 141
#define SPELL_HASTE							 142
#define SPELL_HELLFIRE						 143  /* offensive */
#define SPELL_HERO_FEAST					 144
#define SPELL_HOLD_MONSTER					 145
#define SPELL_HOLD_PERSON					 146
#define SPELL_HOLD_UNDEAD					 147
#define SPELL_ICE_KNIFE						 148
#define SPELL_ICE_STORM						 149  /* offensive */
#define SPELL_ICEBALL						 150  /* offensive */
#define SPELL_ILLUSIONARY_WALL				 151
#define SPELL_IMPROVED_INVIS				 152
#define SPELL_INERTIAL_BARRIER				 153
#define SPELL_INSECT_SUMMONING				 154
#define SPELL_KILL							 155  /* offensive */
#define SPELL_KNOCK							 156
#define SPELL_LIFE_FORCE_TRANSFER			 157
#define SPELL_LIGHT							 158
#define SPELL_LOCATE_PERSON					 159
#define SPELL_METEOR_SWARM					 160  /* offensive */
#define SPELL_MIND_FIRE						 161  /* offensive */
#define SPELL_MIND_HEAL						 162
#define SPELL_MINUTE_METEORS				 163  /* offensive */
#define SPELL_MIRROR_IMAGE					 164
#define SPELL_MONSTER_SUMMONING_I			 165
#define SPELL_MONSTER_SUMMONING_II			 166
#define SPELL_MONSTER_SUMMONING_III			 167
#define SPELL_MONSTER_SUMMONING_IV			 168
#define SPELL_MONSTER_SUMMONING_V			 169
#define SPELL_MYSTIC_BOLT					 170  /* offensive */
#define SPELL_NEGATIVE_PLANE_PROT			 171
#define SPELL_NEMESIS_WEB					 172
#define SPELL_NIGHTMARE						 173
#define SPELL_PARALYSIS						 174
#define SPELL_PASSWALL						 175
#define SPELL_PEACE							 176
#define SPELL_PLAGUE						 177
#define SPELL_PRISMATIC_WALL				 178
#define SPELL_PROT_FROM_ACID				 179
#define SPELL_PROT_FROM_COLD				 180
#define SPELL_PROT_FROM_DRAGON_FEAR 		 181
#define SPELL_PROT_FROM_ELEC				 182
#define SPELL_PROT_FROM_FEAR				 183
#define SPELL_PROT_FROM_FIRE				 184
#define SPELL_PROT_FROM_GAS					 185
#define SPELL_PROT_FROM_GOOD				 186
#define SPELL_PROT_FROM_SUNLIGHT			 187
#define SPELL_PROT_FROM_UNDEAD				 188
#define SPELL_PSYCHIC_CRUSH					 189  /* offensive */
#define SPELL_READ_LANGUAGE					 190
#define SPELL_READ_MAGIC					 191
#define SPELL_REDUCE						 192
#define SPELL_REMOVE_FEAR					 193
#define SPELL_REMOVE_PARALYSIS				 194
#define SPELL_REMOVE_PLAGUE					 195
#define SPELL_RESURRECTION					 196
#define SPELL_SEARING_ORB					 197  /* offensive */
#define SPELL_SHAPECHANGE_BEAR				 198
#define SPELL_SHAPECHANGE_DOLPHIN			 199
#define SPELL_SHAPECHANGE_EAGLE				 200
#define SPELL_SHAPECHANGE_MOUSE				 201
#define SPELL_SHAPECHANGE_OWL				 202
#define SPELL_SHAPECHANGE_TIGER				 203
#define SPELL_SHIELD						 204
#define SPELL_SILENCE						 205
#define SPELL_SLAY_LIVING					 206  /* offensive */
#define SPELL_SLOW							 207
#define SPELL_SOLID_FOG						 208
#define SPELL_SPIKE_STONE					 209  /* offensive */
#define SPELL_SPIRITUAL_HAMMER				 210
#define SPELL_STINK_CLOUD					 211  /* offensive */
#define SPELL_STONESKIN						 212
#define SPELL_SUMMON_SHADOW					 213
#define SPELL_SUMMON_UNDEAD					 214
#define SPELL_TROLL_POWER					 215
#define SPELL_TURN_UNDEAD					 216
#define SPELL_VAMPIRIC_DRAIN				 217  /* offensive */
#define SPELL_VAMPIRIC_TOUCH				 218  /* offensive */
#define SPELL_WALL_OF_FIRE					 219  /* offensive */
#define SPELL_WALL_OF_FOG					 220  /* offensive */
#define SPELL_WALL_OF_FORCE					 221  /* offensive */
#define SPELL_WALL_OF_ICE					 222  /* offensive */
#define SPELL_WALL_OF_IRON					 223  /* offensive */
#define SPELL_WALL_OF_STONE					 224  /* offensive */
#define SPELL_WALL_OF_THORNS				 225  /* offensive */
#define SPELL_WEAKEN						 226
#define SPELL_WEB							 227
#define SPELL_WINDWALL						 228
#define SPELL_WIZARDS_BLADE					 229
#define SPELL_WRAITHFORM					 230
#define SPELL_GROUP_NEG_PLANE_PROT			 231
/** Total Number of defined spells */
#define NUM_SPELLS							 231

/* Insert new spells here, up to MAX_SPELLS */
#define MAX_SPELLS							1500

/* PLAYER SKILLS - Numbered from MAX_SPELLS+1 to MAX_SKILLS */
#define SKILL_BACKSTAB						1501 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_BASH							1502 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_HIDE							1503 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_KICK							1504 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_PICK_LOCK						1505 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_WHIRLWIND						1506
#define SKILL_RESCUE						1507 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_SNEAK							1508 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_STEAL							1509 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_TRACK							1510 /* Reserved Skill[] DO NOT CHANGE */
#define SKILL_LISTEN						1511
#define SKILL_COMMON						1512
#define SKILL_ELVEN							1513
#define SKILL_DARK_ELVEN					1514
#define SKILL_DWARVEN						1515
#define SKILL_DARK_DWARVEN					1516
#define SKILL_HALFLING						1517
#define SKILL_GNOMISH						1518
#define SKILL_DARK_GNOMISH					1519
#define SKILL_GIANT							1520
#define SKILL_MINOTAUR						1521
#define SKILL_LIZARDMAN						1522
#define SKILL_ORCEN							1523
#define SKILL_THIEF_CANT					1524
#define SKILL_SEA_ELVEN						1525
#define SKILL_SAHUAGIN						1526
#define SKILL_KESTRYL						1527
#define SKILL_ABYSS							1528
#define SKILL_ANCIENT_COMMON				1529
#define SKILL_ANCIENT_DWARVEN				1530
#define SKILL_ANCIENT_ELVEN					1531
#define SKILL_ANCIENT_WYRM					1532
#define SKILL_DRAGON						1533
#define SKILL_DRUID_CANT					1534
#define SKILL_GNOLL							1535
#define SKILL_GOBLIN						1536
#define SKILL_MAGIC							1537
#define SKILL_FAIRY							1538
#define SKILL_GARGOYLE						1539
#define SKILL_OGRE							1540
#define SKILL_TREANT						1541
#define SKILL_WERE_TONGUE					1542
#define SKILL_UNDERCOMMON					1543
#define SKILL_TITAN							1544
#define SKILL_BANDAGE						1545
#define SKILL_BLIND_FIGHTING				1546
#define SKILL_BREAK_WEAPON					1547
#define SKILL_BREW							1548
#define SKILL_CAMP							1549
#define SKILL_CLIMBING						1550
#define SKILL_COOK							1551
#define SKILL_CREATE_SPRING					1552
#define SKILL_CRIT_HIT						1553
#define SKILL_DANCE							1554
#define SKILL_DANCE_OF_THE_DEAD				1555
#define SKILL_DIG							1556
#define SKILL_DISARM						1557
#define SKILL_DODGE							1558
#define SKILL_DUAL_WIELD					1559
#define SKILL_ENHANCE_DAMAGE				1560
#define SKILL_ENHANCE_HEAL					1561
#define SKILL_ENHANCE_MOVE					1562
#define SKILL_ENHANCE_SIGHT					1563
#define SKILL_FATAL_BLOW					1564
#define SKILL_FORAGE						1565
#define SKILL_FORGING						1566
#define SKILL_MEDITATION					1567
#define SKILL_MOUNT							1568
#define SKILL_MOVE_SILENTLY					1569
#define SKILL_PARRY							1570
#define SKILL_PLAY_HARP						1571
#define SKILL_PLAY_LYRE						1572
#define SKILL_PLAY_PANPIPE					1573
#define SKILL_REPAIR						1574
#define SKILL_RIDING						1575
#define SKILL_SCRIBE						1576
#define SKILL_SECOND_ATTACK					1577
#define SKILL_SING							1578
#define SKILL_SPEAK							1579
#define SKILL_SWIMMING						1580
#define SKILL_TAME							1581
#define SKILL_THIRD_ATTACK					1582
#define SKILL_THROW							1583
#define SKILL_THROW_AXE						1584
#define SKILL_THROW_BLUDGEONING				1585
#define SKILL_THROW_DAGGER					1586
#define SKILL_THROW_SPEAR					1587
#define SKILL_TRAP							1588
#define SKILL_VENTRILOQUISM					1589
#define SKILL_WIELD_AXE						1590
#define SKILL_WIELD_BLUDGEONING				1591
#define SKILL_WIELD_BOW						1592
#define SKILL_WIELD_CROSSBOW				1593
#define SKILL_WIELD_DAGGER					1594
#define SKILL_WIELD_LONG_BLADE				1595
#define SKILL_WIELD_POLEARM					1596
#define SKILL_WIELD_SHORT_BLADE				1597
#define SKILL_WIELD_SLING					1598
#define SKILL_WRITE							1599
#define SKILL_WRITING						1600
#define SKILL_WIELD_BLOWGUN					1601
#define SKILL_CENTAUR						1602
#define SKILL_PUNCH							1603
/* New skills may be added here up to MAX_SKILLS (2000) */

/* NON-PLAYER AND OBJECT SPELLS AND SKILLS: The practice levels for the spells
 * and skills below are _not_ recorded in the players file; therefore, the
 * intended use is for spells and skills associated with objects (such as
 * SPELL_IDENTIFY used with scrolls of identify) or non-players (such as NPC
 * only spells). */

#define SPELL_IDENTIFY						2001
#define SPELL_FIRE_BREATH					2002
#define SPELL_GAS_BREATH					2003
#define SPELL_FROST_BREATH					2004
#define SPELL_ACID_BREATH					2005
#define SPELL_LIGHTNING_BREATH				2006
#define SPELL_FIRE_SHIELD					2007
#define SPELL_CHILL_SHIELD					2008
#define SPELL_CHANGESTAFF					2009
#define SPELL_VAMPIRIC_DAGGER				2010
#define SPELL_FIRE_DART						2011
#define SPELL_SLEEP_DART					2012
#define SPELL_ACID_DART						2013
#define SPELL_CRITICAL_HIT					2014
/* To make an affect induced by dg_affect look correct on 'stat' we need to
 * define it with a 'spellname'. */
#define SPELL_DG_AFFECT						2998

#define TOP_SPELL_DEFINE					2999
/* NEW NPC/OBJECT SPELLS can be inserted here up to 299 */

/* WEAPON ATTACK TYPES */
#define TYPE_HIT		300
#define TYPE_STING		301
#define TYPE_WHIP		302
#define TYPE_SLASH		303
#define TYPE_BITE		304
#define TYPE_BLUDGEON	305
#define TYPE_CRUSH		306
#define TYPE_POUND		307
#define TYPE_CLAW		308
#define TYPE_MAUL		309
#define TYPE_THRASH		310
#define TYPE_PIERCE		311
#define TYPE_BLAST		312
#define TYPE_PUNCH		313
#define TYPE_STAB		314
/** The total number of attack types */
#define NUM_ATTACK_TYPES	15
#define TYPE_DROWNING	316
/* new attack types can be added here - up to TYPE_SUFFERING */
#define TYPE_SUFFERING	399

#define SAVING_PARA		0
#define SAVING_ROD		1
#define SAVING_PETRI	2
#define SAVING_BREATH	3
#define SAVING_SPELL	4

/***
 **Possible Targets:
 **  TAR_IGNORE    : IGNORE TARGET.
 **  TAR_CHAR_ROOM : PC/NPC in room.
 **  TAR_CHAR_WORLD: PC/NPC in world.
 **  TAR_FIGHT_SELF: If fighting, and no argument, select tar_char as self.
 **  TAR_FIGHT_VICT: If fighting, and no argument, select tar_char as victim (fighting).
 **  TAR_SELF_ONLY : If no argument, select self, if argument check that it IS self.
 **  TAR_NOT_SELF  : Target is anyone else besides self.
 **  TAR_OBJ_INV   : Object in inventory.
 **  TAR_OBJ_ROOM  : Object in room.
 **  TAR_OBJ_WORLD : Object in world.
 **  TAR_OBJ_EQUIP : Object held.
 ***/
#define TAR_IGNORE		(1 << 0)
#define TAR_CHAR_ROOM	(1 << 1)
#define TAR_CHAR_WORLD	(1 << 2)
#define TAR_FIGHT_SELF	(1 << 3)
#define TAR_FIGHT_VICT	(1 << 4)
#define TAR_SELF_ONLY	(1 << 5) /* Only a check, use with i.e. TAR_CHAR_ROOM */
#define TAR_NOT_SELF	(1 << 6) /* Only a check, use with i.e. TAR_CHAR_ROOM */
#define TAR_OBJ_INV		(1 << 7)
#define TAR_OBJ_ROOM	(1 << 8)
#define TAR_OBJ_WORLD	(1 << 9)
#define TAR_OBJ_EQUIP	(1 << 10)

struct spell_info_type {
	byte min_position;	/* Position for caster	 */
	int mana_min;	/* Min amount of mana used by a spell (highest lev) */
	int mana_max;	/* Max amount of mana used by a spell (lowest lev) */
	int mana_change;	/* Change in mana used by spell from lev to lev */

	int min_level[NUM_CLASSES];
	int routines;
	byte violent;
	int targets;         /* See below for use with TAR_XXX  */
	const char *name;	/* Input size not limited. Originates from string constants. */
	const char *wear_off_msg;	/* Input size not limited. Originates from string constants. */
};

/* Possible Targets:
   bit 0 : IGNORE TARGET
   bit 1 : PC/NPC in room
   bit 2 : PC/NPC in world
   bit 3 : Object held
   bit 4 : Object in inventory
   bit 5 : Object in room
   bit 6 : Object in world
   bit 7 : If fighting, and no argument, select tar_char as self
   bit 8 : If fighting, and no argument, select tar_char as victim (fighting)
   bit 9 : If no argument, select self, if argument check that it IS self. */
#define SPELL_TYPE_SPELL	0
#define SPELL_TYPE_POTION	1
#define SPELL_TYPE_WAND		2
#define SPELL_TYPE_STAFF	3
#define SPELL_TYPE_SCROLL	4

#define ASPELL(spellname)  void spellname(int level, struct char_data *ch, struct char_data *victim, struct obj_data *obj)
#define MANUAL_SPELL(spellname)	spellname(level, caster, cvict, ovict);

ASPELL(spell_create_water);
ASPELL(spell_recall);
ASPELL(spell_teleport);
ASPELL(spell_summon);
ASPELL(spell_locate_object);
ASPELL(spell_charm);
ASPELL(spell_information);
ASPELL(spell_identify);
ASPELL(spell_enchant_weapon);
ASPELL(spell_detect_poison);
ASPELL(spell_relocate);
ASPELL(spell_fear);
ASPELL(spell_portal);
ASPELL(spell_recharge);
ASPELL(spell_turn_undead);
ASPELL(spell_flame_blade);

/* basic magic calling functions */
int find_skill_num(char *name);

int mag_damage(int level, struct char_data *ch, struct char_data *victim, int spellnum, int savetype);
void mag_affects(int level, struct char_data *ch, struct char_data *victim, int spellnum, int savetype);
void mag_groups(int level, struct char_data *ch, int spellnum, int savetype);
void mag_masses(int level, struct char_data *ch, int spellnum, int savetype);
void mag_areas(int level, struct char_data *ch, int spellnum, int savetype);
void mag_rooms(int level, struct char_data *ch, int spellnum);
void mag_summons(int level, struct char_data *ch, struct obj_data *obj, int spellnum, int savetype);
void mag_points(int level, struct char_data *ch, struct char_data *victim, int spellnum, int savetype);
void mag_unaffects(int level, struct char_data *ch, struct char_data *victim, int spellnum, int type);
void mag_alter_objs(int level, struct char_data *ch, struct obj_data *obj, int spellnum, int type);
void mag_creations(int level, struct char_data *ch, int spellnum);

int	call_magic(struct char_data *caster, struct char_data *cvict, struct obj_data *ovict, int spellnum, int level, int casttype);
void mag_objectmagic(struct char_data *ch, struct obj_data *obj, char *argument);
int	cast_spell(struct char_data *ch, struct char_data *tch, struct obj_data *tobj, int spellnum);

/* other prototypes */
void spell_level(int spell, int chclass, int level);
void init_spell_levels(void);
const char *skill_name(int num);

/* From magic.c */
int mag_savingthrow(struct char_data *ch, int type, int modifier);
void affect_update(void);

/* from spell_parser.c */
ACMD(do_cast);
void unused_spell(int spl);
void mag_assign_spells(void);

/* Global variables exported */
#ifndef __SPELL_PARSER_C__

extern struct spell_info_type spell_info[];
extern char cast_arg2[];
extern const char *unused_spellname;

#endif /* __SPELL_PARSER_C__ */

#endif /* __SPELLS_H__ */
