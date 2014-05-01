/***************************************************************************************************
*                                                                   Part of the Realms of Tremaria *
* File: spells.c                                                                A CircleMUD/tbaMUD *
* Description: Implementation of "manual spells.                                                   *
*                                                                                                  *
* All rights reserved.  See license for complete information.                                      *
*                                                                                                  *
* Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University                           *
* CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.                                         *
* Last updated: 30 April 2014 -- anth*3                                                            *
***************************************************************************************************/

#include "conf.h"
#include "sysdep.h"

#include "structs.h"
#include "utils.h"
#include "comm.h"
#include "spells.h"
#include "handler.h"
#include "db.h"
#include "constants.h"
#include "interpreter.h"
#include "dg_scripts.h"
#include "act.h"
#include "fight.h"

/* Special spells appear below. */
ASPELL(spell_create_water) {
	int water;

	if (ch == NULL || obj == NULL) {
		return;
	}
	/* level = MAX(MIN(level, LVL_IMPL), 1);	 - not used */
	if (GET_OBJ_TYPE(obj) == ITEM_DRINKCON) {
		if ((GET_OBJ_VAL(obj, 2) != LIQ_WATER) && (GET_OBJ_VAL(obj, 1) != 0)) {
			name_from_drinkcon(obj);
			GET_OBJ_VAL(obj, 2) = LIQ_SLIME;
			name_to_drinkcon(obj, LIQ_SLIME);
		} else {
			water = MAX(GET_OBJ_VAL(obj, 0) - GET_OBJ_VAL(obj, 1), 0);
			if (water > 0) {
				if (GET_OBJ_VAL(obj, 1) >= 0) {
					name_from_drinkcon(obj);
				}
				GET_OBJ_VAL(obj, 2) = LIQ_WATER;
				GET_OBJ_VAL(obj, 1) += water;
				name_to_drinkcon(obj, LIQ_WATER);
				weight_change_object(obj, water);
				act("$p is filled.", FALSE, ch, obj, 0, TO_CHAR);
			}
		}
	}
}

ASPELL(spell_recall) {
	if (victim == NULL || IS_NPC(victim)) {
		return;
	}
	if (ZONE_FLAGGED(GET_ROOM_ZONE(IN_ROOM(victim)), ZONE_NOASTRAL)) {
		send_to_char(ch, "A bright flash prevents your spell from working!");
		return;
	}

	act("$n disappears.", TRUE, victim, 0, 0, TO_ROOM);
	char_from_room(victim);
	char_to_room(victim, r_mortal_start_room);
	act("$n appears in the middle of the room.", TRUE, victim, 0, 0, TO_ROOM);
	look_at_room(victim, 0);
	entry_memory_mtrigger(victim);
	greet_mtrigger(victim, -1);
	greet_memory_mtrigger(victim);
}

ASPELL(spell_teleport) {
	room_rnum to_room;

	if (victim == NULL || IS_NPC(victim)) {
		return;
	}
	if (ZONE_FLAGGED(GET_ROOM_ZONE(IN_ROOM(victim)), ZONE_NOASTRAL)) {
		send_to_char(ch, "A bright flash prevents your spell from working!");
		return;
	}

	do {
		to_room = rand_number(0, top_of_world);
	} while (ROOM_FLAGGED(to_room, ROOM_PRIVATE) || ROOM_FLAGGED(to_room, ROOM_DEATH) ||
			ROOM_FLAGGED(to_room, ROOM_GODROOM) ||
			ZONE_FLAGGED(GET_ROOM_ZONE(to_room), ZONE_CLOSED) ||
			ZONE_FLAGGED(GET_ROOM_ZONE(to_room), ZONE_NOASTRAL));

	act("$n slowly fades out of existence and is gone.", FALSE, victim, 0, 0, TO_ROOM);
	char_from_room(victim);
	char_to_room(victim, to_room);
	act("$n slowly fades into existence.", FALSE, victim, 0, 0, TO_ROOM);
	look_at_room(victim, 0);
	entry_memory_mtrigger(victim);
	greet_mtrigger(victim, -1);
	greet_memory_mtrigger(victim);
}

#define SUMMON_FAIL "You failed.\r\n"

ASPELL(spell_summon) {
	if (ch == NULL || victim == NULL) {
		return;
	}
	if (GET_LEVEL(victim) > MIN(LVL_IMMORT - 1, level + 3)) {
		send_to_char(ch, "%s", SUMMON_FAIL);
		return;
	}

	if (ZONE_FLAGGED(GET_ROOM_ZONE(IN_ROOM(victim)), ZONE_NOASTRAL) ||
			ZONE_FLAGGED(GET_ROOM_ZONE(IN_ROOM(ch)), ZONE_NOASTRAL)) {
		send_to_char(ch, "A bright flash prevents your spell from working!");
		return;
	}

	if (!CONFIG_PK_ALLOWED) {
		if (MOB_FLAGGED(victim, MOB_AGGRESSIVE)) {
			act("As the words escape your lips and $N travels\r\n"
					"through time and space towards you, you realize that $E is\r\n"
					"aggressive and might harm you, so you wisely send $M back.", FALSE, ch, 0,
					victim, TO_CHAR);
			return;
		}
		if (!IS_NPC(victim) && !PRF_FLAGGED(victim, PRF_SUMMONABLE) && !PLR_FLAGGED(victim,
				PLR_KILLER)) {
			send_to_char(victim, "%s just tried to summon you to: %s.\r\n"
					"%s failed because you have summon protection on.\r\n"
					"Type NOSUMMON to allow other players to summon you.\r\n", GET_NAME(ch),
					world[IN_ROOM(ch)].name, (ch->player.sex == SEX_MALE) ? "He" : "She");
			send_to_char(ch, "You failed because %s has summon protection on.\r\n", GET_NAME(victim));
			mudlog(BRF, LVL_IMMORT, TRUE, "%s failed summoning %s to %s.", GET_NAME(ch),
					GET_NAME(victim), world[IN_ROOM(ch)].name);
			return;
		}
	}

	if (MOB_FLAGGED(victim, MOB_NOSUMMON) || (IS_NPC(victim) && mag_savingthrow(victim,
			SAVING_SPELL, 0))) {
		send_to_char(ch, "%s", SUMMON_FAIL);
		return;
	}

	act("$n disappears suddenly.", TRUE, victim, 0, 0, TO_ROOM);
	char_from_room(victim);
	char_to_room(victim, IN_ROOM(ch));
	act("$n arrives suddenly.", TRUE, victim, 0, 0, TO_ROOM);
	act("$n has summoned you!", FALSE, ch, 0, victim, TO_VICT);
	look_at_room(victim, 0);
	entry_memory_mtrigger(victim);
	greet_mtrigger(victim, -1);
	greet_memory_mtrigger(victim);
}

/* Used by the locate object spell to check the alias list on objects */
int isname_obj(char *search, char *list) {
	char *found_in_list; /* But could be something like 'ring' in 'shimmering.' */
	char searchname[128];
	char namelist[MAX_STRING_LENGTH];
	int found_pos = -1;
	int found_name = 0; /* found the name we're looking for */
	int match = 1;
	int i;

	/* Force to lowercase for string comparisons */
	sprintf(searchname, "%s", search);
	for (i = 0; searchname[i]; i++) {
		searchname[i] = LOWER(searchname[i]);
	}
	sprintf(namelist, "%s", list);
	for (i = 0; namelist[i]; i++) {
		namelist[i] = LOWER(namelist[i]);
	}
	/* see if searchname exists any place within namelist */
	found_in_list = strstr(namelist, searchname);
	if (!found_in_list) {
		return 0;
	}

	/*
	 * Found the name in the list, now see if it's a valid hit. The following avoids substrings
	 * (like ring in shimmering) is it at beginning of namelist?
	 */
	for (i = 0; searchname[i]; i++) {
		if (searchname[i] != namelist[i]) {
			match = 0;
		}
	}

	if (match) { /* It was found at the start of the namelist string. */
		found_name = 1;
	} else { /* It is embedded inside namelist. Is it preceded by a space? */
		found_pos = found_in_list - namelist;
		if (namelist[found_pos-1] == ' ') {
			found_name = 1;
		}
	}

	if (found_name) {
		return 1;
	} else {
		return 0;
	}
}

ASPELL(spell_locate_object) {
	struct obj_data *i;
	char name[MAX_INPUT_LENGTH];
	int j;

	if (!obj) {
		send_to_char(ch, "You sense nothing.\r\n");
		return;
	}

	/*  added a global var to catch 2nd arg. */
	sprintf(name, "%s", cast_arg2);

	j = GET_LEVEL(ch) / 2;  /* # items to show = twice char's level */

	for (i = object_list; i && (j > 0); i = i->next) {
		if (!isname_obj(name, i->name)) {
			continue;
		}

		send_to_char(ch, "%c%s", UPPER(*i->short_description), i->short_description + 1);

		if (i->carried_by) {
			send_to_char(ch, " is being carried by %s.\r\n", PERS(i->carried_by, ch));
		} else if (IN_ROOM(i) != NOWHERE) {
			send_to_char(ch, " is in %s.\r\n", world[IN_ROOM(i)].name);
		} else if (i->in_obj) {
			send_to_char(ch, " is in %s.\r\n", i->in_obj->short_description);
		} else if (i->worn_by) {
			send_to_char(ch, " is being worn by %s.\r\n", PERS(i->worn_by, ch));
		} else {
			send_to_char(ch, "'s location is uncertain.\r\n");
		}
		j--;
	}
}

ASPELL(spell_charm) {
	struct affected_type af;

	if (victim == NULL || ch == NULL) {
		return;
	}
	if (victim == ch) {
		send_to_char(ch, "You like yourself even better!\r\n");
	} else if (!IS_NPC(victim) && !PRF_FLAGGED(victim, PRF_SUMMONABLE)) {
		send_to_char(ch, "You fail because SUMMON protection is on!\r\n");
	} else if (AFF_FLAGGED(victim, AFF_SANCTUARY)) {
		send_to_char(ch, "Your victim is protected by sanctuary!\r\n");
	} else if (MOB_FLAGGED(victim, MOB_NOCHARM) || AFF_FLAGGED(victim, AFF_IMMUNE_CHARM)) {
		send_to_char(ch, "Your victim resists!\r\n");
	} else if (AFF_FLAGGED(ch, AFF_CHARM)) {
		send_to_char(ch, "You can't have any followers of your own!\r\n");
	} else if (AFF_FLAGGED(victim, AFF_CHARM) || level < GET_LEVEL(victim)) {
		send_to_char(ch, "You fail.\r\n");
	/* player charming another player - no legal reason for this */
	} else if (!CONFIG_PK_ALLOWED && !IS_NPC(victim)) {
		send_to_char(ch, "You fail - shouldn't be doing it anyway.\r\n");
	} else if (circle_follow(victim, ch)) {
		send_to_char(ch, "Sorry, following in circles is not allowed.\r\n");
	} else if (mag_savingthrow(victim, SAVING_PARA, 0)) {
		send_to_char(ch, "Your victim resists!\r\n");
	} else {
		if (victim->master) {
			stop_follower(victim);
		}
		add_follower(victim, ch);

		new_affect(&af);
		af.spell = SPELL_CHARM;
		af.duration = 24 * 2;
		if (GET_CHA(ch)) {
			af.duration *= GET_CHA(ch);
		}
		if (GET_INT(victim)) {
			af.duration /= GET_INT(victim);
		}
		SET_BIT_AR(af.bitvector, AFF_CHARM);
		affect_to_char(victim, &af);

		act("Isn't $n just such a nice fellow?", FALSE, ch, 0, victim, TO_VICT);
		if (IS_NPC(victim)) {
			REMOVE_BIT_AR(MOB_FLAGS(victim), MOB_SPEC);
		}
	}
}

ASPELL(spell_identify) {
	int i, found, condition;
	size_t len;

	if (obj) {
		char bitbuf[MAX_STRING_LENGTH];

		sprinttype(GET_OBJ_TYPE(obj), item_types, bitbuf, sizeof(bitbuf));
		send_to_char(ch, "You feel informed:\r\nObject '%s', Item type: %s\r\n",
				obj->short_description, bitbuf);

		if (GET_OBJ_AFFECT(obj)) {
			sprintbitarray(GET_OBJ_AFFECT(obj), affected_bits, AF_ARRAY_MAX, bitbuf);
			send_to_char(ch, "Item will give you following abilities:  %s\r\n", bitbuf);
		}

		sprintbitarray(GET_OBJ_EXTRA(obj), extra_bits, EF_ARRAY_MAX, bitbuf);
		send_to_char(ch, "Item is: %s\r\n", bitbuf);

		send_to_char(ch, "Weight: %d, Value: %ld, Rent: %ld, Min. level: %d\r\n", GET_OBJ_WEIGHT(obj),
				GET_OBJ_COST(obj), GET_OBJ_RENT(obj), GET_OBJ_LEVEL(obj));

		switch (GET_OBJ_TYPE(obj)) {
			case ITEM_SCROLL:
			case ITEM_POTION:
				len = i = 0;

				if (GET_OBJ_VAL(obj, 1) >= 1) {
					i = snprintf(bitbuf + len, sizeof(bitbuf) - len, " %s",
							skill_name(GET_OBJ_VAL(obj, 1)));
					if (i >= 0) {
						len += i;
					}
				}
				if (GET_OBJ_VAL(obj, 2) >= 1 && len < sizeof(bitbuf)) {
					i = snprintf(bitbuf + len, sizeof(bitbuf) - len, " %s",
							skill_name(GET_OBJ_VAL(obj, 2)));
					if (i >= 0) {
						len += i;
					}
				}
				if (GET_OBJ_VAL(obj, 3) >= 1 && len < sizeof(bitbuf)) {
					i = snprintf(bitbuf + len, sizeof(bitbuf) - len, " %s",
							skill_name(GET_OBJ_VAL(obj, 3)));
					if (i >= 0) {
						len += i;
					}
				}
				send_to_char(ch, "This %s casts: %s\r\n", item_types[(int) GET_OBJ_TYPE(obj)], bitbuf);
				break;
			case ITEM_WAND:
			case ITEM_STAFF:
				send_to_char(ch, "This %s casts: %s\r\nIt has %ld maximum charge%s and %ld remaining.\r\n",
						item_types[(int) GET_OBJ_TYPE(obj)], skill_name(GET_OBJ_VAL(obj, 3)),
						GET_OBJ_VAL(obj, 1), GET_OBJ_VAL(obj, 1) == 1 ? "" : "s",
						GET_OBJ_VAL(obj, 2));
				break;
			case ITEM_WEAPON:
				send_to_char(ch, "Damage Dice is '%ldD%ld' for an average per-round damage of %.1f.\r\n",
						GET_OBJ_VAL(obj, 1), GET_OBJ_VAL(obj, 2), ((GET_OBJ_VAL(obj, 2) + 1) / 2.0) *
						GET_OBJ_VAL(obj, 1));
				break;
			case ITEM_ARMOR:
				send_to_char(ch, "AC-apply is %ld\r\n", GET_OBJ_VAL(obj, 0));
				break;
		}
		found = FALSE;
		for (i = 0; i < MAX_OBJ_AFFECT; i++) {
			if ((obj->affected[i].location != APPLY_NONE) && (obj->affected[i].modifier != 0)) {
				if (!found) {
					send_to_char(ch, "Can affect you as :\r\n");
					found = TRUE;
				}
				sprinttype(obj->affected[i].location, apply_types, bitbuf, sizeof(bitbuf));
				send_to_char(ch, "   Affects: %s By %d\r\n", bitbuf, obj->affected[i].modifier);
			}
		}
		condition = (GET_OBJ_CSLOTS(obj) * 100) / GET_OBJ_TSLOTS(obj);

		if ((GET_OBJ_CSLOTS(obj) == 0) && (GET_OBJ_TSLOTS(obj) == 0)) {
			send_to_char(ch, "Quality: INDESTRUCTABLE\r\n");
			found = TRUE;
		}
		if ((GET_LEVEL(ch) >= LVL_IMMORT) && (!found)) {
			send_to_char(ch, "Quality: %d/%d\r\nCondition: %d percent\r\n", GET_OBJ_CSLOTS(obj),
					GET_OBJ_TSLOTS(obj), condition);
			found = TRUE;
		}
		if ((condition <= 10) && (!found)) {
			send_to_char(ch, "Quality: Extremley Poor\r\n");
			found = TRUE;
		}
		if ((condition <= 20) && (!found)) {
			send_to_char(ch, "Quality: Poor\r\n");
			found = TRUE;
		}
		if ((condition <= 30) && (!found)) {
			send_to_char(ch, "Quality: Fair\r\n");
			found = TRUE;
		}
		if ((condition <= 40) && (!found)) {
			send_to_char(ch, "Quality: Moderate\r\n");
			found = TRUE;
		}
		if ((condition <= 50) && (!found)) {
			send_to_char(ch, "Quality: Good\r\n");
			found = TRUE;
		}
		if ((condition <= 60) && (!found)) {
			send_to_char(ch, "Quality: Very Good\r\n");
			found = TRUE;
		}
		if ((condition <= 70) && (!found)) {
			send_to_char(ch, "Quality: Excellent\r\n");
			found = TRUE;
		}
		if ((condition <= 80) && (!found)) {
			send_to_char(ch, "Quality: Superior\r\n");
			found = TRUE;
		}
		if ((condition <= 90) && (!found)) {
			send_to_char(ch, "Quaity: Extremely Superior\r\n");
			found = TRUE;
		}
		if ((condition <= 100) && (!found)) {
			send_to_char(ch, "Quality: Brand New\r\n");
			found = TRUE;
		}
	} else if (victim) {		/* victim */
		send_to_char(ch, "Name: %s\r\n", GET_NAME(victim));
		if (!IS_NPC(victim)) {
			send_to_char(ch, "%s is %d years, %d months, %d days and %d hours old.\r\n",
					GET_NAME(victim), age(victim)->year, age(victim)->month,
					age(victim)->day, age(victim)->hours);
		}
		send_to_char(ch, "Height %d cm, Weight %d pounds\r\n", GET_HEIGHT(victim),
				GET_WEIGHT(victim));
		send_to_char(ch, "Level: %d, Hits: %d, Mana: %d\r\n", GET_LEVEL(victim), GET_HIT(victim),
				GET_MANA(victim));
		send_to_char(ch, "AC: %d, Hitroll: %d, Damroll: %d\r\n", compute_armor_class(victim),
				GET_HITROLL(victim), GET_DAMROLL(victim));
		send_to_char(ch, "Str: %d/%d, Int: %d, Wis: %d, Dex: %d, Con: %d, Cha: %d\r\n",
				GET_STR(victim), GET_ADD(victim), GET_INT(victim), GET_WIS(victim), GET_DEX(victim),
				GET_CON(victim), GET_CHA(victim));
	}
}

/*
 * Cannot use this spell on an equipped object or it will mess up the wielding character's hit/dam
 * totals.
 */
ASPELL(spell_enchant_weapon) {
	int i;

	if (ch == NULL || obj == NULL) {
		return;
	}
	/* Either already enchanted or not a weapon. */
	if (GET_OBJ_TYPE(obj) != ITEM_WEAPON || OBJ_FLAGGED(obj, ITEM_MAGIC)) {
		return;
	}

	/* Make sure no other affections. */
	for (i = 0; i < MAX_OBJ_AFFECT; i++) {
		if (obj->affected[i].location != APPLY_NONE) {
			return;
		}
	}

	SET_BIT_AR(GET_OBJ_EXTRA(obj), ITEM_MAGIC);

	obj->affected[0].location = APPLY_HITROLL;
	obj->affected[0].modifier = 1 + (level >= 18);

	obj->affected[1].location = APPLY_DAMROLL;
	obj->affected[1].modifier = 1 + (level >= 20);

	if (IS_GOOD(ch)) {
		SET_BIT_AR(GET_OBJ_EXTRA(obj), ITEM_ANTI_EVIL);
		act("$p glows blue.", FALSE, ch, obj, 0, TO_CHAR);
	} else if (IS_EVIL(ch)) {
		SET_BIT_AR(GET_OBJ_EXTRA(obj), ITEM_ANTI_GOOD);
		act("$p glows red.", FALSE, ch, obj, 0, TO_CHAR);
	} else {
		act("$p glows yellow.", FALSE, ch, obj, 0, TO_CHAR);
	}
}

ASPELL(spell_detect_poison) {
	if (victim) {
		if (victim == ch) {
			if (AFF_FLAGGED(victim, AFF_POISON)) {
				send_to_char(ch, "You can sense poison in your blood.\r\n");
			} else {
				send_to_char(ch, "You feel healthy.\r\n");
			}
		} else {
			if (AFF_FLAGGED(victim, AFF_POISON)) {
				act("You sense that $E is poisoned.", FALSE, ch, 0, victim, TO_CHAR);
			} else {
				act("You sense that $E is healthy.", FALSE, ch, 0, victim, TO_CHAR);
			}
		}
	}

	if (obj) {
		switch (GET_OBJ_TYPE(obj)) {
			case ITEM_DRINKCON:
			case ITEM_FOUNTAIN:
			case ITEM_FOOD:
				if (GET_OBJ_VAL(obj, 3)) {
					act("You sense that $p has been contaminated.",FALSE,ch,obj,0,TO_CHAR);
				} else {
					act("You sense that $p is safe for consumption.", FALSE, ch, obj, 0, TO_CHAR);
				}
				break;
			default:
				send_to_char(ch, "You sense that it should not be consumed.\r\n");
		}
	}
}

/*
 * Rather pathetic modify of SUMMON straight from Circle 3.0 beta 8, but it works just fine...for
 * simplicity I left it linked to the NOSUMM flag for whether or not you are allowed to relocate to
 * that PC/NPC, but anyone can change it as they see fit...I though of restricting relocating to
 * mobs at all, but a nosumm flag should take care of mobs you don't want relocated to...if you make
 * any improvements I'd appreciate it if you send me your new version...
 *
 *                                                 Daniel W. Burke
 *                                                 dwb@ix.netcom.com
 */
ASPELL(spell_relocate) {
	if (ch == NULL || victim == NULL) {
		return;
	}
	if (GET_LEVEL(victim) > MIN(LVL_IMMORT - 1, level + 3)) {
		send_to_char(ch, SUMMON_FAIL);
		return;
	}
	if (MOB_FLAGGED(victim, MOB_NOSUMMON)) {
		send_to_char(ch, SUMMON_FAIL);
		return;
	}
	if (!CONFIG_PK_ALLOWED) {
		if (MOB_FLAGGED(victim, MOB_AGGRESSIVE)) {
			act("As the words escape your lips and a rift travels\r\n"
					"through time and space toward $N, you realize that $E is\r\n"
					"aggressive and might harm you, so you wisely close it.", FALSE, ch, 0, victim,
					TO_CHAR);
			return;
		}
		if (!IS_NPC(victim) && !PRF_FLAGGED(victim, PRF_SUMMONABLE) && !PLR_FLAGGED(victim,
				PLR_KILLER)) {
			send_to_char(victim, "%s just tried to relocate to you.\r\n"
					"%s failed because you have summon protection on.\r\n"
					"Type NOSUMMON to allow other players to relocate to you.\r\n", GET_NAME(ch),
					(ch->player.sex == SEX_MALE) ? "He" : "She");

			send_to_char(ch, "You failed because %s has summon protection on.\r\n", GET_NAME(victim));

			mudlog(BRF, LVL_IMMORT, TRUE, "%s failed relocating to %s at %s.", GET_NAME(ch),
					GET_NAME(victim), world[ch->in_room].name);
			return;
		}
	}

	act("$n opens a portal and steps through it.", TRUE, ch, 0, 0, TO_ROOM);
	act("You open a portal and step through.", FALSE, ch, 0, 0, TO_CHAR);
	char_from_room(ch);
	char_to_room(ch, victim->in_room);
	act("A portal opens and $n steps out.", TRUE, ch, 0, 0, TO_ROOM);
	look_at_room(ch, 0);
}


ASPELL(spell_fear) {
	struct char_data *target = (struct char_data *) victim;
	struct char_data *next_target;
	int rooms_to_flee = 0;

	ACMD(do_flee);

	if (ch == NULL) {
		return;
	}
	if (AFF_FLAGGED(victim, AFF_IMMUNE_FEAR)) {
		return;
	}
	send_to_char(ch, "You radiate an aura of fear into the room!\r\n");
	act("$n is surrounded by an aura of fear!", TRUE, ch, 0, 0, TO_ROOM);

	for (target = world[ch->in_room].people; target; target = next_target) {
		next_target = target->next_in_room;

		if (target == NULL) {
			return;
		}
		if (target == ch) {
			continue;
		}
		if (GET_LEVEL(target) >= LVL_IMMORT) {
			continue;
		}

		if (mag_savingthrow(target, SAVING_SPELL, 0)) {
			act("$n is unaffected by the fear!\r\n", TRUE, ch, 0, GET_NAME(target), TO_ROOM);
			if (IS_NPC(target)) {
				hit(target, ch, TYPE_UNDEFINED);
			}
		} else {
			for (rooms_to_flee = level / 10; rooms_to_flee > 0; rooms_to_flee--) {
				send_to_char(target, "You flee in terror!\r\n");
				do_flee(target, "", 0, 0);
			}
		}
	}
}

/* Define the OBJ_VNUMs */
#define PORTAL			31
#define FLAME_BLADE		100

/* Create a magic portal */
ASPELL(spell_portal) {
	struct obj_data *tmp_obj, *tmp_obj2;
	struct extra_descr_data *ed;
	struct room_data *rp, *nrp;
	struct char_data *tmp_ch = (struct char_data *) victim;
	char buf[MAX_STRING_LENGTH];

	assert(ch);
	assert((level >= 0) && (level <= LVL_IMPL));

	/* Check target room for legality */
	rp = &world[ch->in_room];
	tmp_obj = read_object(PORTAL, VIRTUAL);
	if (!rp || !tmp_obj) {
		send_to_char(ch, "The magic fails\r\n");
		extract_obj(tmp_obj);
		return;
	}
	if (IS_SET_AR(rp->room_flags, ROOM_NOMAGIC)) {
		send_to_char(ch, "Eldritch wizardry obstructs thee.\r\n");
		extract_obj(tmp_obj);
		return;
	}
	if (IS_SET_AR(rp->room_flags, ROOM_TUNNEL)) {
		send_to_char(ch, "There is no room in here to summon!\r\n");
		extract_obj(tmp_obj);
		return;
	}
	if (!(nrp = &world[tmp_ch->in_room])) {
		char str[180];

		sprintf(str, "%s not in any room", GET_NAME(tmp_ch));
		log(str);
		send_to_char(ch, "The magic cannot locate the target\r\n");
		extract_obj(tmp_obj);
		return;
	}
	if (ROOM_FLAGGED(tmp_ch->in_room, ROOM_NOMAGIC)) {
		send_to_char(ch, "Your target is protected against your magic.\r\n");
		extract_obj(tmp_obj);
		return;
	}

	sprintf(buf, "Through the mists of the portal, you can faintly see %s", nrp->name);

	CREATE(ed, struct extra_descr_data, 1);
	ed->next = tmp_obj->ex_description;
	tmp_obj->ex_description = ed;
	CREATE(ed->keyword, char, strlen(tmp_obj->name) + 1);
	strcpy(ed->keyword, tmp_obj->name);
	ed->description = strdup(buf);

	tmp_obj->obj_flags.value[0] = level / 5;
	tmp_obj->obj_flags.value[1] = tmp_ch->in_room;

	obj_to_room(tmp_obj, ch->in_room);

	act("$p suddenly appears.", TRUE, ch, tmp_obj, 0, TO_ROOM);
	act("$p suddenly appears.", TRUE, ch, tmp_obj, 0, TO_CHAR);

	/* Portal at other side */
	rp = &world[ch->in_room];
	tmp_obj2 = read_object(PORTAL, VIRTUAL);
	if (!rp || !tmp_obj2) {
		send_to_char(ch, "The magic fails\r\n");
		extract_obj(tmp_obj2);
		return;
	}
	sprintf(buf, "Through the mists of the portal, you can faintly see %s", rp->name);

	CREATE(ed, struct extra_descr_data, 1);
	ed->next = tmp_obj2->ex_description;
	tmp_obj2->ex_description = ed;
	CREATE(ed->keyword, char, strlen(tmp_obj2->name) + 1);
	strcpy(ed->keyword, tmp_obj2->name);
	ed->description = strdup(buf);

	tmp_obj2->obj_flags.value[0] = level / 5;
	tmp_obj2->obj_flags.value[1] = ch->in_room;

	obj_to_room(tmp_obj2, tmp_ch->in_room);

	act("$p suddenly appears.", TRUE, tmp_ch, tmp_obj2, 0, TO_ROOM);
	act("$p suddenly appears.", TRUE, tmp_ch, tmp_obj2, 0, TO_CHAR);
}

ASPELL(spell_recharge) {
	int restored_charges = 0, explode = 0;

	if (ch == NULL || obj == NULL) {
		return;
	}
	/* This is on my mud, comment off on yours */
	if (OBJ_FLAGGED(obj, ITEM_NO_RECHARGE)) {
		send_to_char(ch, "This item cannot be recharged.\r\n");
		return;
	}

	if (GET_OBJ_TYPE(obj) == ITEM_WAND) {
		if (GET_OBJ_VAL(obj, 2) < GET_OBJ_VAL(obj, 1)) {
			send_to_char(ch, "You attempt to recharge the wand.\r\n");
			restored_charges = rand_number(1, 5);
			GET_OBJ_VAL(obj, 2) += restored_charges;
			if (GET_OBJ_VAL(obj, 2) > GET_OBJ_VAL(obj, 1)) {
				send_to_char(ch, "The wand is overcharged and explodes!\r\n");
				act("$n overcharges $p and it explodes!", TRUE, ch, obj, 0, TO_NOTVICT);
				explode = dice(GET_OBJ_VAL(obj, 2), 2);
				GET_HIT(ch) -= explode;
				update_pos(ch);
				extract_obj(obj);
				return;
			} else {
				send_to_char(ch, "You restore %d charges to the wand.\r\n", restored_charges);
				return;
			}
		} else {
			send_to_char(ch, "That item is already at full charges!\r\n");
			return;
		}
	} else if (GET_OBJ_TYPE(obj) == ITEM_STAFF) {
		if (GET_OBJ_VAL(obj, 2) < GET_OBJ_VAL(obj, 1)) {
			send_to_char(ch, "You attempt to recharge the staff.\r\n");
			restored_charges = rand_number(1, 3);
			GET_OBJ_VAL(obj, 2) += restored_charges;
			if (GET_OBJ_VAL(obj, 2) > GET_OBJ_VAL(obj, 1)) {
				send_to_char(ch, "The staff is overcharged and explodes!\r\n");
				act("$n overcharges $s and it explodes!", TRUE, ch, obj, 0, TO_NOTVICT);
				explode = dice(GET_OBJ_VAL(obj, 2), 3);
				GET_HIT(ch) -= explode;
				update_pos(ch);
				extract_obj(obj);
				return;
			} else {
				send_to_char(ch, "You restore %d charges to the staff.\r\n", restored_charges);
				return;
			}
		} else {
			send_to_char(ch, "That item is already at full charges!\r\n");
			return;
		}
	}
}

ASPELL(spell_turn_undead) {
	int rooms_to_flee = 0;
	ACMD(do_flee);
	void die(struct char_data *victim, struct char_data *ch);

	if (ch == NULL || victim == NULL) {
		return;
	}
	if (victim->player.chrace != RACE_UNDEAD) {
		return;
	}
	send_to_char(ch, "You radiate an aura of grace from your deity!\r\n");
	act("$n is surrounded by an aura of grace!", TRUE, ch, 0, 0, TO_ROOM);
	if (IS_NPC(victim)) {
		if (GET_LEVEL(ch) >= 45) {
			if (mag_savingthrow(victim, SAVING_SPELL, 0) && !rand_number(0, 5)) {
				act("$n is dissolved by your spell!", TRUE, ch, 0, victim, TO_ROOM);
				send_to_char(ch, "Your victim dissolves before your eyes!\r\n");
				die(victim, ch);
			} else if (rand_number(0, 9) > 1) {
				for (rooms_to_flee = level / 10; rooms_to_flee > 0; rooms_to_flee--) {
					send_to_char(victim, "You have been turned!\r\n");
					do_flee(victim, "", 0, 0);
				}
			} else {
				hit(victim, ch, TYPE_UNDEFINED);
			}
		} else {
			if (rand_number(0, 9) > 1) {
				for (rooms_to_flee = level / 10; rooms_to_flee > 0; rooms_to_flee--) {
					send_to_char(victim, "You have been turned!\r\n");
					do_flee(victim, "", 0, 0);
				}
			} else {
				hit(victim, ch, TYPE_UNDEFINED);
			}
		}
	} else {
		if (rand_number(0, 9) > 1) {
			for (rooms_to_flee = level / 10; rooms_to_flee > 0; rooms_to_flee--) {
				send_to_char(victim, "You have been turned!\r\n");
				do_flee(victim, "", 0, 0);
			}
		}
	}
}

ASPELL(spell_flame_blade) {
	struct obj_data *tmp_obj;
	struct extra_descr_data *ed;
	struct room_data *rp;
	char buf[MAX_STRING_LENGTH];

	assert(ch);
	assert((level >= 0) && (level <= LVL_IMPL));

	tmp_obj = read_object(FLAME_BLADE, VIRTUAL);
	rp = &world[ch->in_room];
	if (!rp || !tmp_obj) {
		send_to_char(ch, "The magic fails\r\n");
		extract_obj(tmp_obj);
		return;
	}
	if (IS_SET_AR(rp->room_flags, ROOM_NOMAGIC)) {
		send_to_char(ch, "Eldritch wizardry obstructs thee.\r\n");
		extract_obj(tmp_obj);
		return;
	}
	CREATE(ed, struct extra_descr_data, 1);
	ed->next = tmp_obj->ex_description;
	tmp_obj->ex_description = ed;
	CREATE(ed->keyword, char, strlen(tmp_obj->name) + 1);
	strcpy(ed->keyword, tmp_obj->name);
	ed->description = strdup(buf);
	tmp_obj->obj_flags.value[0] = 4 + (GET_LEVEL(ch) % 2);
	obj_to_char(tmp_obj, ch);
	act("$p suddenly appears.", TRUE, ch, tmp_obj, 0, TO_CHAR);
}
