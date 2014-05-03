/***************************************************************************************************
*                                                                   Part of the Realms of Tremaria *
* File: constants.c                                                             A CircleMUD/tbaMUD *
* Description: Numeric and string contants used by the MUD.                                        *
*                                                                                                  *
* @todo Come up with a standard for descriptive arrays. Either all end with newlines or all of     *
* them don not.                                                                                    *
*                                                                                                  *
* All rights reserved.  See license for complete information.                                      *
*                                                                                                  *
* Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University                           *
* CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.                                         *
* Last updated: 2 May 2014 -- anth*3                                                               *
***************************************************************************************************/

#include "conf.h"
#include "sysdep.h"

#include "structs.h"
#include "utils.h"
#include "interpreter.h"	/* alias_data */

/** Current tbaMUD version.
 * @todo defined with _TBAMUD so we don't have multiple constants to change.
 * @todo cpp_extern isn't needed here (or anywhere) as the extern reserved word works correctly with
 * C compilers (at least in my Experience)
 * Jeremy Osborne 1/28/2008
 */
cpp_extern const char *tbamud_version = "tbaMUD 3.65";

/* strings corresponding to ordinals/bitvectors in structs.h */
/* (Note: strings for class definitions in class.c instead of here) */

/**
 * Description of cardinal directions.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *dirs[] = {
	"north",
	"east",
	"south",
	"west",
	"up",
	"down",
	"northwest", /* Diagonals only used if CONFIG_DIAGONAL_DIRS is set */
	"northeast",
	"southeast",
	"southwest",
	"in",
	"out",
	"\n"
};

const char *dirs2[] = {
	"the north",
	"the east",
	"the south",
	"the west",
	"above",
	"below",
	"the northwest",
	"the northeast",
	"the southeast",
	"the southwest",
	"in",
	"out",
	"\n"
};

const char *autoexits[] = {
	"n",
	"e",
	"s",
	"w",
	"u",
	"d",
	"nw",
	"ne",
	"se",
	"sw",
	"i",
	"o",
	"\n"
};

/**
 * Room flag descriptions.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *room_bits[] = {
	"DARK",
	"DEATH",
	"NO_MOB",
	"INDOORS",
	"PEACEFUL",
	"SOUNDPROOF",
	"NO_TRACK",
	"NO_MAGIC",
	"TUNNEL",
	"PRIVATE",
	"GODROOM",
	"HOUSE",
	"HCRSH",
	"ATRIUM",
	"OLC",
	"*",				/* The BFS Mark. */
	"WORLDMAP",
	"GOOD_REGEN",
	"BETTER_REGEN",
	"ANTI_GOOD",
	"ANTI_EVIL",
	"DESERT",
	"ARCTIC",
	"STABLE",
	"ARENA",
	"RIVER",
	"\n"
};

const char *room_affections[] = {
	"WALLFOG",
	"WALLFIRE",
	"WALLTHORNS",
	"STINK",
	"FOGCLOUD",
	"WINDWALL",
	"ILLUSWALL",
	"SOLIDFOG",
	"WALLICE",
	"WALLFORCE",
	"WALLIRON",
	"WALLSTONE",
	"DEATHFOG",
	"PRISMWALL",
	"FAIRYFOG",
	"ACIDCLOUD",
	"ACIDPOOL",
	"BLACKSTORM",
	"BLADEBARRIER",
	"ENTANGLE",
	"NEM_WEB",
	"SPIKESTONE",
	"DARKNESS",
	"/n"
};

/**
 * Room flag descriptions. (ZONE_x)
 * @pre Must be in the same order as the defines in structs.h.
 * Must end array with a single newline.
 */
const char *zone_bits[] = {
	"CLOSED",
	"NO_IMMORT",
	"QUEST",
	"GRID",
	"NOBUILD",
	"!ASTRAL",
	"WORLDMAP",
	"\n"
};

/**
 * Exit bits for doors.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *exit_bits[] = {
	"DOOR",
	"CLOSED",
	"LOCKED",
	"PICKPROOF",
	"HIDDEN",
	"\n"
};

/**
 * Description of the room sector type.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *sector_types[] = {
	"Inside",
	"City",
	"Field",
	"Forest",
	"Hills",
	"Mountains",
	"Water (Swim)",
	"Water (No Swim)",
	"In Flight",
	"Underwater",
	"Road",
	"Wall",
	"Lava",
	"\n"
};

/**
 * PC and NPC sex.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *genders[] = {
	"neutral",
	"male",
	"female",
	"\n"
};

const char *languages[] = {
    "common",
    "elven",
    "dark elven",
    "dwarven",
    "dark dwarven",
    "halfling",
    "gnomish",
    "dark gnomish",
    "giant",
    "minotaur",
    "lizardman",
    "orcen",
    "thieves' cant",
    "sea elven",
    "sahuagin",
    "kestryl",
    "abyss",
    "ancient common",
    "ancient dwarven",
    "ancient elven",
    "ancient wyrm",
    "dragon",
    "druid cant",
    "gnoll",
    "goblin",
    "magic",
    "fairy",
    "gargoyle",
    "ogre",
    "treant",
    "were-tongue",
    "undercommon",
    "titan",
    "\n"
};

/** Character positions.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline. */
const char *position_types[] = {
	"Dead",
	"Mortally wounded",
	"Incapacitated",
	"Stunned",
	"Sleeping",
	"Resting",
	"Sitting",
	"Fighting",
	"Standing",
	"Riding",
	"\n"
};

/**
 * Player flags.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *player_bits[] = {
	"KILLER",
	"THIEF",
	"FROZEN",
	"DONTSET",
	"WRITING",
	"MAILING",
	"CSH",
	"SITEOK",
	"NOSHOUT",
	"NOTITLE",
	"DELETED",
	"LOADRM",
	"NO_WIZL",
	"NO_DEL",
	"INVST",
	"CRYO",
	"DEAD",		/* You should never see this flag on a character in game. */
	"IBT_BUG",
	"IBT_IDEA",
	"IBT_TYPO",
	"!AUTOTITLE",
	"UNUSED2",
	"UNUSED3",
	"UNUSED4",
	"UNUSED5",
	"\n"
};

/**
 * Mob action flags.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *action_bits[] = {
	"SPEC",
	"SENTINEL",
	"SCAVENGER",
	"ISNPC",
	"AWARE",
	"AGGR",
	"STAY-ZONE",
	"WIMPY",
	"AGGR_EVIL",
	"AGGR_GOOD",
	"AGGR_NEUTRAL",
	"MEMORY",
	"HELPER",
	"!CHARM",
	"!SUMMN",
	"!SLEEP",
	"!BASH",
	"!BLIND",
	"!KILL",
	"DEAD",				/* You should never see this. */
	"PET",
	"ETHEREAL",
	"FASTREGEN",
	"HUNT",
	"SHIP",
	"!BURN",
	"+BURN",
	"!FREEZE",
	"+FREEZE",
	"!ACID",
	"+ACID",
	"CAN_BURN",
	"CAN_FREEZE",
	"CAN_ACID",
	"GAZE_PETRIFY",
	"CANT_FLEE",
	"MOUNTABLE",
	"SUMMON",
	"\n"
};

/**
 * PC Preference flags.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *preference_bits[] = {
	"BRIEF",
	"COMPACT",
	"!SHOUT",
	"!TELL",
	"D_HP",
	"D_MANA",
	"D_MOVE",
	"AUTOEX",
	"!HASS",
	"QUEST",
	"SUMN",
	"!REPEAT",
	"LIGHT",
	"C1",
	"C2",
	"!WIZ",
	"L1",
	"L2",
	"!AUC",
	"!GOSSIP",
	"!GRATZ",
	"RMFLG",
	"D_AUTO",
	"CLS",
	"BLDWLK",
	"AFK",
	"AUTOLOOT",
	"AUTOGOLD",
	"AUTOSPLIT",
	"AUTOSAC",
	"AUTOASSIST",
	"AUTOMAP",
	"AUTOKEY",
	"AUTODOOR",
	"RMFLAGS",
	"D_GOLD",
	"D_XP",
	"D_DAM",
	"D_FIG",
	"VET",
	"RET",
	"A_RED",
	"A_BLUE",
	"BOUNTY",
	"ASSASSIN",
	"!QUIT",
	"!SPORT",
	"AUTOTITL",
	"\n"
};

/**
 * Affected bits.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *affected_bits[] = {
	"\0", 				/* DO NOT REMOVE!! */
	"BLIND",
	"INVIS",
	"DET-ALIGN",
	"DET-INVIS",
	"DET-MAGIC",
	"SENSE-LIFE",
	"WATWALK",
	"SANCT",
	"GROUP",
	"CURSE",
	"INFRA",
	"POISON",
	"PROT-EVIL",
	"PROT-GOOD",
	"SLEEP",
	"NO_TRACK",
	"FLY",
	"SCUBA",
	"SNEAK",
	"HIDE",
	"UNUSED",
	"CHARM",
	"SHIELD",
	"DEATHDANCE",
	"PROT-FIRE",
	"PROT-COLD",
	"IMM-POISON",
	"IMM-FEAR",
	"IMM-FIRE",
	"IMM-COLD",
	"IMM-LTNG",
	"IMM-GAS",
	"IMM-ACID",
	"IMM-HOLDS",
	"IMM-SLEEP",
	"IMM-CHARM",
	"IMM-DRG-FEAR",
	"MIRRORIMAGE",
	"STONESKIN",
	"FARSEE",
	"ENH_HEAL",
	"ENH_MANA",
	"ENH_MOVE",
	"HOLDPERSON",
	"CRITHIT",
	"BURNING",
	"FREEZING",
	"ACIDED",
	"BLINK",
	"HASTE",
	"LYC",
	"VAMP",
	"ZOMB",
	"DAY-BURNS",
	"SUPER-STR",
	"REGEN",
	"PASSDOOR",
	"PLUS1",
	"PLUS2",
	"PLUS3",
	"PLUS4",
	"PLUS5",
	"SILVER",
	"RELICS",
	"TAMED",
	"DOCILE",
	"WED",
	"LIGHT",
	"COMP_LANG",
	"CAST_SUM",
	"\n"
};

/**
 * Connection type descriptions.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *connected_types[] = {
	"Playing",
	"Disconnecting",
	"Get name",
	"Confirm name",
	"Get password",
	"Get new PW",
	"Confirm new PW",
	"Select sex",
	"Select class",
	"Reading MOTD",
	"Main Menu",
	"Get descript.",
	"Changing PW 1",
	"Changing PW 2",
	"Changing PW 3",
	"Self-Delete 1",
	"Self-Delete 2",
	"Disconnecting",
	"Object edit",
	"Room edit",
	"Zone edit",
	"Mobile edit",
	"Shop edit",
	"Text edit",
	"Config edit",
	"Social edit",
	"Trigger edit",
	"Help edit",
	"Quest edit",
	"Preference edit",
	"IBT edit",
	"Message edit",
	"Protocol Detection",
	"Select race",
	"Roll stats",
	"Starting town",
	"\n"
};

/**
 * Describes the position in the equipment listing.
 * @pre Must be in the same order as the defines.
 * Not used in sprinttype() so no \n.
 */
const char *wear_where[] = {
	"<used as light>      ",
	"<worn on finger>     ",
	"<worn on finger>     ",
	"<worn around neck>   ",
	"<worn around neck>   ",
	"<worn on body>       ",
	"<worn on head>       ",
	"<worn on legs>       ",
	"<worn on feet>       ",
	"<worn on hands>      ",
	"<worn on arms>       ",
	"<worn as shield>     ",
	"<worn about body>    ",
	"<worn about waist>   ",
	"<worn around wrist>  ",
	"<worn around wrist>  ",
	"<wielded>            ",
	"<held>               ",
	"<worn on back>       ",
	"<worn on face>       ",
	"<dual-wield>         "
};

/*
 * Describes where an item can be worn.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *equipment_types[] = {
	"Used as light",
	"Worn on right finger",
	"Worn on left finger",
	"First worn around Neck",
	"Second worn around Neck",
	"Worn on body",
	"Worn on head",
	"Worn on legs",
	"Worn on feet",
	"Worn on hands",
	"Worn on arms",
	"Worn as shield",
	"Worn about body",
	"Worn around waist",
	"Worn around right wrist",
	"Worn around left wrist",
	"Wielded",
	"Held",
	"Worn on back",
	"Worn on face",
	"Dual-wielded",
	"\n"
};

/**
 * Describes the type of object.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *item_types[] = {
	"UNDEFINED",
	"LIGHT",
	"SCROLL",
	"WAND",
	"STAFF",
	"WEAPON",
	"FURNITURE",
	"FREE",
	"TREASURE",
	"ARMOR",
	"POTION",
	"WORN",
	"OTHER",
	"TRASH",
	"FREE2",
	"CONTAINER",
	"NOTE",
	"LIQ CONTAINER",
	"KEY",
	"FOOD",
	"MONEY",
	"PEN",
	"BOAT",
	"FOUNTAIN",
	"\n"
};

/**
 * Describes the wear flags set on an item.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *wear_bits[] = {
	"TAKE",
	"FINGER",
	"NECK",
	"BODY",
	"HEAD",
	"LEGS",
	"FEET",
	"HANDS",
	"ARMS",
	"SHIELD",
	"ABOUT",
	"WAIST",
	"WRIST",
	"WIELD",
	"HOLD",
	"DUALWIELD",
	"BACK",
	"FACE",
	"\n"
};

/**
 * Describes the extra flags applied to an item.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *extra_bits[] = {
	"GLOW",
	"HUM",
	"!RENT",
	"!DONATE",
	"!INVIS",
	"INVISIBLE",
	"MAGIC",
	"!DROP",
	"BLESS",
	"!GOOD",
	"!EVIL",
	"!NEUTRAL",
	"!MAGE",
	"!NECROMANCER",
	"!CLERIC",
	"!DRUID",
	"!WARRIOR",
	"!PALADIN",
	"!ANTI-PALADIN",
	"!RANGER",
	"!MONK",
	"!BARD",
	"!THIEF",
	"!SELL",
	"QUEST",
	"NEWBIE",
	"!RECHARGE",
	"BURIED",
	"WEDDING",
	"FIRE",
	"COLD",
	"ACID",
	"GAS",
	"!HUMAN",
	"!HALF-ELF",
	"!ELF",
	"!DARK-ELF",
	"!SEA-ELF",
	"!DWARF",
	"!DARK-DWARF",
	"!HALFLING",
	"!GNOME",
	"!DARK-GNOME",
	"!HALF-GIANT",
	"!MINOTAUR",
	"!LIZARDMAN",
	"!SAHUAGIN",
	"!KESTRYL",
	"!CENTAUR",
	"!LICH",
	"!VAMPIRE",
	"!ZOMBIE",
	"!WEREWOLF",
	"+1",
	"+2",
	"+3",
	"+4",
	"+5",
	"SILVER",
	"!BREAK",
	"RETURNING",
	"ENGRAVED",
	"2HANDED",
	"AUTOENGRAVE",
	"DUALWIELD",
	"IMMORTAL",
	"ELECT",
	"SPELL",
	"\n"
};

/**
 * Describes the apply types.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *apply_types[] = {
	"NONE",
	"STR",
	"DEX",
	"INT",
	"WIS",
	"CON",
	"CHA",
	"CLASS",
	"LEVEL",
	"AGE",
	"CHAR_WEIGHT",
	"CHAR_HEIGHT",
	"MAXMANA",
	"MAXHIT",
	"MAXMOVE",
	"GOLD",
	"EXP",
	"ARMOR",
	"HITROLL",
	"DAMROLL",
	"SAVING_PARA",
	"SAVING_ROD",
	"SAVING_PETRI",
	"SAVING_BREATH",
	"SAVING_SPELL",
	"RACE",
	"SIZE",
	"\n"
};

/**
 * Describes the closure mechanism for a container.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *container_bits[] = {
	"CLOSEABLE",
	"PICKPROOF",
	"CLOSED",
	"LOCKED",
	"\n"
};

/**
 * Describes the liquid description.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *drinks[] = {
	"water",
	"beer",
	"wine",
	"ale",
	"dark ale",
	"whisky",
	"lemonade",
	"firebreather",
	"local speciality",
	"slime mold juice",
	"milk",
	"tea",
	"coffee",
	"blood",
	"salt water",
	"clear water",
	"\n"
};

/**
 * Describes a one word alias for each type of liquid.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *drinknames[] = {
	"water",
	"beer",
	"wine",
	"ale",
	"ale",
	"whisky",
	"lemonade",
	"firebreather",
	"local",
	"juice",
	"milk",
	"tea",
	"coffee",
	"blood",
	"salt",
	"water",
	"\n"
};

/**
 * Define the effect of liquids on hunger, thirst, and drunkenness, in that
 * order. See values.doc for more information.
 * @pre Must be in the same order as the defines.
 */
int drink_aff[][3] = {
	{0, 1, 10},
	{3, 2, 5},
	{5, 2, 5},
	{2, 2, 5},
	{1, 2, 5},
	{6, 1, 4},
	{0, 1, 8},
	{10, 0, 0},
	{3, 3, 3},
	{0, 4, -8},
	{0, 3, 6},
	{0, 1, 6},
	{0, 1, 6},
	{0, 2, -1},
	{0, 1, -2},
	{0, 0, 13}
};

/**
 * Describes the color of the various drinks.
 * @pre Must be in the same order as the defines.
 * Must end array with a single newline.
 */
const char *color_liquid[] = {
	"clear",
	"brown",
	"clear",
	"brown",
	"dark",
	"golden",
	"red",
	"green",
	"clear",
	"light green",
	"white",
	"brown",
	"black",
	"red",
	"clear",
	"crystal clear",
	"\n"
};

/**
 * Used to describe the level of fullness of a drink container. Not used in sprinttype() so no \n.
 */
const char *fullness[] = {
	"less than half ",
	"about half ",
	"more than half ",
	""
};

/**
 * Strength attribute affects.
 * The fields are hit mod, damage mod, weight carried mod, and weight wielded mod.
 */
cpp_extern const struct str_app_type str_app[] = {
	{-5, -4, 0, 0},		/* str = 0 */
	{-5, -4, 3, 1},		/* str = 1 */
	{-3, -2, 3, 2},
	{-3, -1, 10, 3},
	{-2, -1, 25, 4},
	{-2, -1, 55, 5},	/* str = 5 */
	{-1, 0, 80, 6},
	{-1, 0, 90, 7},
	{0, 0, 100, 8},
	{0, 0, 100, 9},
	{0, 0, 115, 10},	/* str = 10 */
	{0, 0, 115, 11},
	{0, 0, 140, 12},
	{0, 0, 140, 13},
	{0, 0, 170, 14},
	{0, 0, 170, 15},	/* str = 15 */
	{0, 1, 195, 16},
	{1, 1, 220, 18},
	{1, 2, 255, 20},	/* str = 18 */
	{3, 7, 640, 40},
	{3, 8, 700, 40},	/* str = 20 */
	{4, 9, 810, 40},
	{4, 10, 970, 40},
	{5, 11, 1130, 40},
	{6, 12, 1440, 40},
	{7, 14, 1750, 40},	/* str = 25 */
	{1, 3, 280, 22},	/* str = 18/0 - 18-50 */
	{2, 3, 305, 24},	/* str = 18/51 - 18-75 */
	{2, 4, 330, 26},	/* str = 18/76 - 18-90 */
	{2, 5, 380, 28},	/* str = 18/91 - 18-99 */
	{3, 6, 480, 30}		/* str = 18/100 */
};

/**
 * Dexterity skill modifiers for thieves.
 * The fields are for pick pockets, pick locks, find traps, sneak and hide.
 */
cpp_extern const struct dex_skill_type dex_app_skill[] = {
	{-99, -99, -90, -99, -60},	/* dex = 0 */
	{-90, -90, -60, -90, -50},	/* dex = 1 */
	{-80, -80, -40, -80, -45},
	{-70, -70, -30, -70, -40},
	{-60, -60, -30, -60, -35},
	{-50, -50, -20, -50, -30},	/* dex = 5 */
	{-40, -40, -20, -40, -25},
	{-30, -30, -15, -30, -20},
	{-20, -20, -15, -20, -15},
	{-15, -10, -10, -20, -10},
	{-10, -5, -10, -15, -5},	/* dex = 10 */
	{-5, 0, -5, -10, 0},
	{0, 0, 0, -5, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},			/* dex = 15 */
	{0, 5, 0, 0, 0},
	{5, 10, 0, 5, 5},
	{10, 15, 5, 10, 10},		/* dex = 18 */
	{15, 20, 10, 15, 15},
	{15, 20, 10, 15, 15},		/* dex = 20 */
	{20, 25, 10, 15, 20},
	{20, 25, 15, 20, 20},
	{25, 25, 15, 20, 20},
	{25, 30, 15, 25, 25},
	{25, 30, 15, 25, 25}		/* dex = 25 */
};

/**
 * Dexterity attribute affects.
 * The fields are reaction, missile attacks, and defensive (armor class).
 */
cpp_extern const struct dex_app_type dex_app[] = {
	{-7, -7, 6},	/* dex = 0 */
	{-6, -6, 5},	/* dex = 1 */
	{-4, -4, 5},
	{-3, -3, 4},
	{-2, -2, 3},
	{-1, -1, 2},	/* dex = 5 */
	{0, 0, 1},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},		/* dex = 10 */
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, -1},		/* dex = 15 */
	{1, 1, -2},
	{2, 2, -3},
	{2, 2, -4},		/* dex = 18 */
	{3, 3, -4},
	{3, 3, -4},		/* dex = 20 */
	{4, 4, -5},
	{4, 4, -5},
	{4, 4, -5},
	{5, 5, -6},
	{5, 5, -6}		/* dex = 25 */
};

/**
 * Constitution attribute affects.
 * The field referenced is for hitpoint bonus.
 */
cpp_extern const struct con_app_type con_app[] = {
	{-4, 20},		/* con = 0 */
	{-3, 25},		/* con = 1 */
	{-2, 30},
	{-2, 35},
	{-1, 40},
	{-1, 45},		/* con = 5 */
	{-1, 50},
	{0,	 55},
	{0,	 60},
	{0,	 65},
	{0,	 70},		/* con = 10 */
	{0,  75},
	{0,  80},
	{0,  85},
	{0,  88},
	{1,  90},		/* con = 15 */
	{2,  95},
	{2,  97},
	{3,  99},		/* con = 18 */
	{3,  99},
	{4,  99},		/* con = 20 */
	{5,  99},
	{5,  99},
	{5,  99},
	{6,  99},
	{6,  99}		/* con = 25 */
};

/**
 * Intelligence attribute affects.
 * The field shows how much practicing affects a skill/spell.
 */
cpp_extern const struct int_app_type int_app[] = {
	{3},		/* int = 0 */
	{5},		/* int = 1 */
	{7},
	{8},
	{9},
	{10},		/* int = 5 */
	{11},
	{12},
	{13},
	{15},
	{17},		/* int = 10 */
	{19},
	{22},
	{25},
	{30},
	{35},		/* int = 15 */
	{40},
	{45},
	{50},		/* int = 18 */
	{53},
	{55},		/* int = 20 */
	{56},
	{57},
	{58},
	{59},
	{60}		/* int = 25 */
};

/**
 * Wisdom attribute affects.
 * The field represents how many extra practice points are gained per level.
 */
cpp_extern const struct wis_app_type wis_app[] = {
	{0},	/* wis = 0 */
	{0},  /* wis = 1 */
	{0},
	{0},
	{0},
	{0},  /* wis = 5 */
	{0},
	{0},
	{0},
	{0},
	{0},  /* wis = 10 */
	{0},
	{2},
	{2},
	{3},
	{3},  /* wis = 15 */
	{3},
	{4},
	{5},	/* wis = 18 */
	{6},
	{6},  /* wis = 20 */
	{6},
	{6},
	{7},
	{7},
	{7}  /* wis = 25 */
};

/**
 * Define a set of opposite directions from the cardinal directions.
 */
int rev_dir[] = {
	SOUTH,
	WEST,
	NORTH,
	EAST,
	DOWN,
	UP,
	SOUTHEAST,
	SOUTHWEST,
	NORTHWEST,
	NORTHEAST,
	IN,
	OUT
};

/**
 * How much movement is lost moving through a particular sector type.
 */
int movement_loss[] = {
	1,	/* Inside     */
	1,	/* City       */
	2,	/* Field      */
	3,	/* Forest     */
	4,	/* Hills      */
	6,	/* Mountains  */
	4,	/* Swimming   */
	1,	/* Unswimable */
	1,	/* Flying     */
	5,	/* Underwater */
	3,	/* Road       */
	5, 	/* Wall       */
	6	/* Lava       */
};

/** The names of the days of the mud week. Not used in sprinttype(). */
const char *weekdays[] = {
	"the Day of the Earth",
	"the Day of all Races",
	"the Day of Darkness",
	"the Day of Light",
	"the Day of the Stars",
	"the Day of the Sun",
	"the Day of the Gods"
};

/** The names of the mud months. Not used in sprinttype(). */
const char *month_name[] = {
	"Month of the Dawn",        /* 0 */
	"Month of Spring",
	"Month of Full Bloom",
	"Month of Fertility",
	"Month of Nature",
	"Month of the High Sun",     /* 5 */
	"Month of Summer",
	"Month of the Heat",
	"Month of the Sunsets",
	"Month of Autumn",
	"Month of the Moon",         /* 10 */
	"Month of the Harvest",
	"Month of the Fading",
	"Month of Long Shadows",
	"Month of Winter",
	"Month of Hibernation",      /* 15 */
	"Month of the Storms"
};

const char *year_name[] = {
	"Year of the Dragon",         /* 0 */
	"Year of the Shooting Star",
	"Year of the Tomb",
	"Year of the Broken Blade",
	"Year of the Golden Goblet",
	"Year of the Bull",         /* 5 */
	"Year of the Raven",
	"Year of Pain",
	"Year of the Winter Wolf",
	"Year of the Moat",
	"Year of the Groaning Cart",        /* 10 */
	"Year of the Flame Tongue",
	"Year of the Runes",
	"Year of the Battle",
	"Year of the Dawn Rose",
	"Year of the Curse",        /* 15 */
	"Year of the Wyvern",
	"Year of the Empty Hand",
	"Year of the Awakening",
	"Year of the Cold Claws",
	"Year of the Longhorns",         /* 20 */
	"Year of the Watching Woods",
	"Year of the Blood Rose",
	"Year of the Toppled Tree",
	"Year of the Frost Giant",
	"Year of the Dusty Throne",        /* 25 */
	"Year of the Rock",
	"Year of the Shattered Wall",
	"Year of the Oak",
	"Year of the Serpant",
	"Year of the Falcon",           /* 30 */
	"Year of the Basilisk",
	"Year of Thunder",
	"Year of the Trumpet",
	"Year of the Iron Fist",
	"Year of the Great Harvest",           /* 35 */
	"Year of the Mists",
	"Year of the Black Hound",
	"Year of the Scorpion",
	"Year of the Stag",
	"Year of the Knight",            /* 40 */
	"Year of the Whistling Wind",
	"Year of the Griffon",
	"Year of Wandering",
	"Year of the Crumbling Keep",
	"Year of the Great Evil",    /* 45 */
	"Year of the Lost Helm",
	"Year of the Saddle",
	"Year of the Arch",
	"Year of the Lion"
	"Year of the Maidens",     /* 50 */
	"Year of the Staff",
	"Year of the Harp",
	"Year of Princes and Lords",
	"Year of the Blue Shield",
	"Year of the Spiked Mace",    /* 55 */
	"Year of the Crown",
	"Year of the Spur",
	"Year of the Bridle",
	"Year of the Bow",
	"Year of the Wyrm",    /* 60 */
	"Year of the Purple Banner",
	"Year of the Rogue Dragons",
	"Year of the Haunting",
	"Year of Unknown Magic",
	"Year of Shadows",     /* 65 */
	"Year of the Skull",
	"Year of the Yellow Rose",
	"Year of the Yeti",
	"Year of the Strike",
	"Year of the Souls",      /* 70 */
	"Year of the Treants",
	"Year of Fire",
	"Year of Frost",
	"Year of Doom"
};

/** Names for mob trigger types. */
const char *trig_types[] = {
	"Global",
	"Random",
	"Command",
	"Speech",
	"Act",
	"Death",
	"Greet",
	"Greet-All",
	"Entry",
	"Receive",
	"Fight",
	"HitPrcnt",
	"Bribe",
	"Load",
	"Memory",
	"Cast",
	"Leave",
	"Door",
	"UNUSED",
	"Time",
	"\n"
};

/** Names for object trigger types. */
const char *otrig_types[] = {
	"Global",
	"Random",
	"Command",
	"UNUSED1",
	"UNUSED2",
	"Timer",
	"Get",
	"Drop",
	"Give",
	"Wear",
	"UNUSED3",
	"Remove",
	"UNUSED4",
	"Load",
	"UNUSED5",
	"Cast",
	"Leave",
	"UNUSED6",
	"Consume",
	"Time",
	"\n"
};

/** Names for world (room) trigger types. */
const char *wtrig_types[] = {
	"Global",
	"Random",
	"Command",
	"Speech",
	"UNUSED1",
	"Zone Reset",
	"Enter",
	"Drop",
	"UNUSED2",
	"UNUSED3",
	"UNUSED4",
	"UNUSED5",
	"UNUSED6",
	"UNUSED7",
	"UNUSED8",
	"Cast",
	"Leave",
	"Door",
	"Login",
	"Time",
	"\n"
};

/** The names of the different channels that history is stored for.
 * @todo Only referenced by do_history at the moment. Should be moved local
 * to that function. */
const char *history_types[] = {
	"all",
	"say",
	"gossip",
	"wiznet",
	"tell",
	"shout",
	"grats",
	"holler",
	"auction",
	"\n"
};

/** Flag names for Ideas, Bugs and Typos (defined in ibt.h) */
const char *ibt_bits[] = {
	"Resolved",
	"Important",
	"InProgress",
	"\n"
};

const char *npc_class_types[] = {
	"Other",
	"Undead",
	"Humanoid",
	"Animal",
	"Dragon",
	"Giant",
	"\n"
};

const char *size[] = {
	"Tiny",
	"Small",
	"Medium",
	"Large",
	"Huge",
	"Gargantuan",
	"\n"
};

const char *religion[] = {
	"Implementor",
	"Nature",
	"Magic",
	"Music",
	"Beauty",
	"War",
	"Healing",
	"Decay",
	"Wisdom",
	"Deception",
	"Creation",
	"Death",
	"Justice",
	"Vengence",
	"Industry",
	"\n"
};

const char *zeal[] = {
	"Patron",
	"Renegade",
	"God of Nature",
	"God of Magic",
	"God of Music",
	"God of Beauty",
	"God of War",
	"God of Healing",
	"God of Decay",
	"God of Wisdom",
	"God of Deception",
	"God of Creation",
	"God of Death",
	"God of Justice",
	"God of Vengence",
	"God of Industry",
	"Greater Good",
	"Greater Evil",
	"Greater Neutrality",
	"Chaos",
	"\n"
};
/* --- End of constants arrays. --- */

/*
 * Various arrays we count so we can check the world files.  These
 * must be at the bottom of the file so they're pre-declared.
 */
/** Number of defined room bit descriptions. */
size_t	room_bits_count = sizeof(room_bits) / sizeof(room_bits[0]) - 1,
/** Number of defined action bit descriptions. */
action_bits_count = sizeof(action_bits) / sizeof(action_bits[0]) - 1,
/** Number of defined affected bit descriptions. */
affected_bits_count = sizeof(affected_bits) / sizeof(affected_bits[0]) - 1,
/** Number of defined extra bit descriptions. */
extra_bits_count = sizeof(extra_bits) / sizeof(extra_bits[0]) - 1,
/** Number of defined wear bit descriptions. */
wear_bits_count = sizeof(wear_bits) / sizeof(wear_bits[0]) - 1;
