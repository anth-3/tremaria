/***************************************************************************************************
*                                                                   Part of the Realms of Tremaria *
* File: act.offensive.c                                                         A CircleMUD/tbaMUD *
* Description: Player-level commands of an offensive nature.                                       *
*                                                                                                  *
* All rights reserved.  See license for complete information.                                      *
*                                                                                                  *
* Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University                           *
* CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.                                         *
* Last updated: 20 May 2014 -- anth*3                                                              *
***************************************************************************************************/

#include "conf.h"
#include "sysdep.h"

#include "structs.h"
#include "utils.h"
#include "comm.h"
#include "interpreter.h"
#include "handler.h"
#include "db.h"
#include "spells.h"
#include "act.h"
#include "fight.h"
#include "mud_event.h"

/* extern variables */
extern int pk_allowed;

/* extern functions */
void perform_wear(struct char_data *ch, struct obj_data *obj, int where);
/*bool range_hit(struct char_data *ch, struct char_data * victim, struct obj_data *obj);*/
bool fire_at_char(struct char_data *ch, struct char_data * list, struct obj_data * obj, int dir);

ACMD(do_assist) {
	char arg[MAX_INPUT_LENGTH];
	struct char_data *helpee, *opponent;

	if (FIGHTING(ch)) {
		send_to_char(ch, "You are already fighting!  How can you assist someone else?\r\n");
		return;
	}
	one_argument(argument, arg);

	if (!*arg) {
		send_to_char(ch, "Whom do you wish to assist?\r\n");
	} else if (!(helpee = get_char_vis(ch, arg, NULL, FIND_CHAR_ROOM))) {
		send_to_char(ch, "%s", CONFIG_NOPERSON);
	} else if (helpee == ch) {
		send_to_char(ch, "You cannot help yourself any more than this!\r\n");
	} else {
		/* Hit the same enemy the person you're helping is. */
		if (FIGHTING(helpee)) {
			opponent = FIGHTING(helpee);
		} else
			for (opponent = world[IN_ROOM(ch)].people; opponent && (FIGHTING(opponent) != helpee);
		opponent = opponent->next_in_room);

		if (!opponent) {
			act("But nobody is fighting $M!", FALSE, ch, 0, helpee, TO_CHAR);
		} else if (!CAN_SEE(ch, opponent)) {
			act("You cannot see who is fighting $M!", FALSE, ch, 0, helpee, TO_CHAR);
			/* prevent accidental pkill */
		} else if (!CONFIG_PK_ALLOWED && !IS_NPC(opponent) && !CAN_MURDER(ch, opponent)) {
			act("Use 'murder' if you really want to attack $N.", FALSE, ch, 0, opponent, TO_CHAR);
		} else {
			send_to_char(ch, "You join the fight!\r\n");
			act("$N assists you!", 0, helpee, 0, ch, TO_CHAR);
			act("$n assists $N.", FALSE, ch, 0, helpee, TO_NOTVICT);
			hit(ch, opponent, TYPE_UNDEFINED);
		}
	}
}

ACMD(do_hit) {
	char arg[MAX_INPUT_LENGTH];
	struct char_data *vict;
	char my_buffer[256];

	one_argument(argument, arg);

	if (!*arg) {
		send_to_char(ch, "Hit who?\r\n");
	} else if (!(vict = get_char_vis(ch, arg, NULL, FIND_CHAR_ROOM))) {
		send_to_char(ch, "They do not seem to be here.\r\n");
	} else if (vict == ch) {
		send_to_char(ch, "You hit yourself...OUCH!.\r\n");
		act("$n hits $mself, and says OUCH!", FALSE, ch, 0, vict, TO_ROOM);
	} else if (AFF_FLAGGED(ch, AFF_CHARM) && (ch->master == vict)) {
		act("$N is just such a good friend, you simply cannot hit $M.", FALSE, ch, 0, vict, TO_CHAR);
	} else if (MOB_FLAGGED(vict, MOB_SHIP) && !MOB_FLAGGED(ch, MOB_SHIP)) {
		send_to_char(ch, "That is just not possible.\r\n");
	} else {
		if (!CONFIG_PK_ALLOWED && !IS_NPC(vict) && !IS_NPC(ch)) {
			check_killer(ch, vict);
		}
		if (!ROOM_FLAGGED(ch->in_room, ROOM_ARENA)) {
			if (!pk_allowed) {
				if (!IS_NPC(vict) && !IS_NPC(ch)  && !CAN_MURDER(ch, vict) &&
						(subcmd != SCMD_MURDER)) {
					send_to_char(ch, "Use 'murder' to hit another player.\r\n");
					return;
				}
				if (subcmd == SCMD_MURDER && !CAN_MURDER(ch, vict)) {
					send_to_char(ch, "The laws of Tremaria explicitly state that you cannot kill another player.\r\n");
					sprintf(my_buffer, "%s tried to murder %s, but was not covered by Tremarian Law.", GET_NAME(ch), GET_NAME(vict));
					log(my_buffer);
					return;
				}
				if (IS_AFFECTED(ch, AFF_CHARM) && !IS_NPC(ch->master) && !IS_NPC(vict)) {
					return;			/* you can't order a charmed pet to attack a player */
				}
			}
		}
		if (ROOM_FLAGGED(ch->in_room, ROOM_ARENA)) {
			sprintf(my_buffer, "%s and %s engage in mortal combat!!!\r\n", GET_NAME(ch), GET_NAME(vict));
/*			sportschan(my_buffer);*/
		}
		if ((GET_POS(ch) == POS_STANDING) && (vict != FIGHTING(ch))) {
			if (GET_DEX(ch) > GET_DEX(vict) || (GET_DEX(ch) == GET_DEX(vict) &&
					rand_number(1, 2) == 1)) {  /* if faster */
				hit(ch, vict, TYPE_UNDEFINED);  /* first */
			} else {
				hit(vict, ch, TYPE_UNDEFINED);  /* or the victim is first */
			}
			WAIT_STATE(ch, PULSE_VIOLENCE + 2);
		} else {
			send_to_char(ch, "You are fighting the best you can!\r\n");
		}
	}
}

ACMD(do_kill) {
	char arg[MAX_INPUT_LENGTH];
	struct char_data *vict;

	if (GET_LEVEL(ch) < LVL_IMMORT || IS_NPC(ch) || !PRF_FLAGGED(ch, PRF_NOHASSLE)) {
		do_hit(ch, argument, cmd, subcmd);
		return;
	}
	one_argument(argument, arg);

	if (!*arg) {
		send_to_char(ch, "Kill who?\r\n");
	} else {
		if (!(vict = get_char_vis(ch, arg, NULL, FIND_CHAR_ROOM))) {
			send_to_char(ch, "They are not here.\r\n");
		} else if (ch == vict) {
			send_to_char(ch, "Your mother would be so sad.. :(\r\n");
		} else {
			act("You chop $M to pieces!  Ah!  The blood!", FALSE, ch, 0, vict, TO_CHAR);
			act("$N chops you to pieces!", FALSE, vict, 0, ch, TO_CHAR);
			act("$n brutally slays $N!", FALSE, ch, 0, vict, TO_NOTVICT);
			raw_kill(vict, ch);
		}
	}
}

ACMD(do_backstab) {
	char buf[MAX_INPUT_LENGTH];
	struct char_data *vict;
	int percent, prob;

	if (IS_NPC(ch) || !GET_SKILL(ch, SKILL_BACKSTAB)) {
	send_to_char(ch, "You have no idea how to do that.\r\n");
	return;
	}

	one_argument(argument, buf);

	if (!(vict = get_char_vis(ch, buf, NULL, FIND_CHAR_ROOM))) {
		send_to_char(ch, "Backstab who?\r\n");
		return;
	}
	if (vict == ch) {
		send_to_char(ch, "How can you sneak up on yourself?\r\n");
		return;
	}
	if (!GET_EQ(ch, WEAR_WIELD)) {
		send_to_char(ch, "You need to wield a weapon to make it a success.\r\n");
		return;
	}
	if (GET_OBJ_VAL(GET_EQ(ch, WEAR_WIELD), 3) != TYPE_PIERCE - TYPE_HIT) {
		send_to_char(ch, "Only piercing weapons can be used for backstabbing.\r\n");
		return;
	}
	if (FIGHTING(vict)) {
		send_to_char(ch, "You cannot backstab a fighting person -- they are too alert!\r\n");
		return;
	}
	if (!CAN_MURDER(ch, vict)) {
		send_to_char(ch, "You cannot backstab a person you cannot murder under Tremarian Law!\r\n");
		return;
	}
	if (MOB_FLAGGED(vict, MOB_SHIP) && !MOB_FLAGGED(ch, MOB_SHIP)) {
		send_to_char(ch, "That just is not possible.\r\n");
		return;
	}
	if (MOB_FLAGGED(vict, MOB_AWARE) && AWAKE(vict)) {
		act("You notice $N lunging at you!", FALSE, vict, 0, ch, TO_CHAR);
		act("$e notices you lunging at $m!", FALSE, vict, 0, ch, TO_VICT);
		act("$n notices $N lunging at $m!", FALSE, vict, 0, ch, TO_NOTVICT);
		hit(vict, ch, TYPE_UNDEFINED);
		return;
	}

	percent = rand_number(1, 101);	/* 101% is a complete failure */
	prob = GET_SKILL(ch, SKILL_BACKSTAB);

	if (AWAKE(vict) && (percent > prob)) {
		damage(ch, vict, 0, SKILL_BACKSTAB);
	} else {
		hit(ch, vict, SKILL_BACKSTAB);
	}
	WAIT_STATE(ch, 2 * PULSE_VIOLENCE);
}

ACMD(do_order) {
	char name[MAX_INPUT_LENGTH], message[MAX_INPUT_LENGTH];
	bool found = FALSE;
	struct char_data *vict;
	struct follow_type *k;

	half_chop(argument, name, message);

	if (!*name || !*message) {
		send_to_char(ch, "Order who to do what?\r\n");
	} else if (!(vict = get_char_vis(ch, name, NULL, FIND_CHAR_ROOM)) &&
			!is_abbrev(name, "followers")) {
		send_to_char(ch, "That person is not here.\r\n");
	} else if (ch == vict) {
		send_to_char(ch, "You obviously suffer from skitzofrenia.\r\n");
	} else {
		if (AFF_FLAGGED(ch, AFF_CHARM)) {
			send_to_char(ch, "Your superior would not approve of you giving orders.\r\n");
			return;
		}
		if (vict) {
			char buf[MAX_STRING_LENGTH];

			snprintf(buf, sizeof(buf), "$N orders you to '%s'", message);
			act(buf, FALSE, vict, 0, ch, TO_CHAR);
			act("$n gives $N an order.", FALSE, ch, 0, vict, TO_ROOM);

			if ((vict->master != ch) || !AFF_FLAGGED(vict, AFF_CHARM)) {
				act("$n has an indifferent look.", FALSE, vict, 0, 0, TO_ROOM);
			} else {
				send_to_char(ch, "%s", CONFIG_OK);
				command_interpreter(vict, message);
			}
		} else {			/* This is order "followers" */
			char buf[MAX_STRING_LENGTH];

			snprintf(buf, sizeof(buf), "$n issues the order '%s'.", message);
			act(buf, FALSE, ch, 0, 0, TO_ROOM);

			for (k = ch->followers; k; k = k->next) {
				if (IN_ROOM(ch) == IN_ROOM(k->follower)) {
					if (AFF_FLAGGED(k->follower, AFF_CHARM)) {
					found = TRUE;
					command_interpreter(k->follower, message);
					}
				}
			}
			if (found) {
				send_to_char(ch, "%s", CONFIG_OK);
			} else {
				send_to_char(ch, "Nobody here is a loyal subject of yours!\r\n");
			}
		}
	}
}

ACMD(do_flee) {
	int i, attempt, loss;
	struct char_data *was_fighting;

	if (GET_POS(ch) < POS_FIGHTING) {
		send_to_char(ch, "You are in pretty bad shape, unable to flee!\r\n");
		return;
	}

	for (i = 0; i < 6; i++) {
		attempt = rand_number(0, DIR_COUNT - 1); /* Select a random direction */
		if (CAN_GO(ch, attempt) && !ROOM_FLAGGED(EXIT(ch, attempt)->to_room, ROOM_DEATH)) {
			act("$n panics, and attempts to flee!", TRUE, ch, 0, 0, TO_ROOM);
			was_fighting = FIGHTING(ch);
			if (do_simple_move(ch, attempt, TRUE)) {
				send_to_char(ch, "You flee head over heels.\r\n");
				if (was_fighting && !IS_NPC(ch)) {
					loss = GET_MAX_HIT(was_fighting) - GET_HIT(was_fighting);
					loss *= GET_LEVEL(was_fighting);
					gain_exp(ch, -loss);
				}
				if (FIGHTING(ch)) {
					stop_fighting(ch);
				}
				if (was_fighting && ch == FIGHTING(was_fighting)) {
					stop_fighting(was_fighting);
				}
			} else {
				act("$n tries to flee, but cannot!", TRUE, ch, 0, 0, TO_ROOM);
			}
			return;
		}
	}
	send_to_char(ch, "PANIC!  You could not escape!\r\n");
}

ACMD(do_bash) {
	char arg[MAX_INPUT_LENGTH];
	struct char_data *vict;
	int percent, prob;
	struct follow_type *k;

	one_argument(argument, arg);

	if (IS_MAGE(ch) || IS_NECROMANCER(ch) || IS_CLERIC(ch) || IS_DRUID(ch) || IS_BARD(ch) ||
			IS_THIEF(ch)) {
    	send_to_char(ch, "You had better leave all the martial arts to fighters.\r\n");
    	return;
  	}

	if (IS_NPC(ch) || !GET_SKILL(ch, SKILL_BASH)) {
		send_to_char(ch, "You have no idea how.\r\n");
		return;
	}
	if (ROOM_FLAGGED(IN_ROOM(ch), ROOM_PEACEFUL)) {
		send_to_char(ch, "This room just has such a peaceful, easy feeling...\r\n");
		return;
	}
	if (!GET_EQ(ch, WEAR_SHIELD)) {
		send_to_char(ch, "You need to wield a shield to make it a success.\r\n");
		return;
	}
	if (!(vict = get_char_vis(ch, arg, NULL, FIND_CHAR_ROOM))) {
		if (FIGHTING(ch) && IN_ROOM(ch) == IN_ROOM(FIGHTING(ch))) {
			vict = FIGHTING(ch);
		} else {
			send_to_char(ch, "Bash who?\r\n");
			return;
		}
	}
	if (vict == ch) {
		send_to_char(ch, "Are we not funny today...\r\n");
		return;
	}
	if (MOB_FLAGGED(vict, MOB_NOKILL)) {
		send_to_char(ch, "This mob is protected.\r\n");
		return;
	}
	if (!IS_NPC(vict) && !IS_NPC(ch) && !CAN_MURDER(ch, vict)) {
		send_to_char(ch, "Type 'murder' if you want to attack that person.\r\n");
		return;
	}
	if (MOB_FLAGGED(vict, MOB_SHIP) && !MOB_FLAGGED(ch, MOB_SHIP)) {
		send_to_char(ch, "That just is not possible.\r\n");
		return;
	}

	percent = rand_number(1, 101);	/* 101% is a complete failure */
	prob = GET_SKILL(ch, SKILL_BASH);

	if (MOB_FLAGGED(vict, MOB_NOBASH)) {
		percent = 101;
	}
	if (percent > prob) {
		damage(ch, vict, 0, SKILL_BASH);
		GET_POS(ch) = POS_SITTING;
	} else {
		/*
		 * If we bash a player and they wimp out, they will move to the previous room before we set
		 * them sitting.  If we try to set the victim sitting first to make sure they don't flee,
		 * then we can't bash them!  So now we only set them sitting if they didn't flee.
		 * -gg 9/21/98
		 */
		if ((GET_SIZE(ch) - GET_SIZE(vict)) > -2) {
			damage(ch, vict, 15, SKILL_BASH);
			if (!MOB_FLAGGED(vict, MOB_NOBASH)) {
				GET_POS(vict) = POS_SITTING;
			}
			for (k = ch->followers; k; k=k->next) {
				if (PRF_FLAGGED(k->follower, PRF_AUTOASSIST) &&
						(k->follower->in_room == ch->in_room)) {
					do_assist(k->follower, GET_NAME(ch), 0, 0);
				}
			}
			WAIT_STATE(vict, PULSE_VIOLENCE);
		} else {
			damage(ch, vict, 7, SKILL_BASH);
			for (k = ch->followers; k; k=k->next) {
				if (PRF_FLAGGED(k->follower, PRF_AUTOASSIST) &&
						(k->follower->in_room == ch->in_room)) {
					do_assist(k->follower, GET_NAME(ch), 0, 0);
				}
			}
			WAIT_STATE(vict, PULSE_VIOLENCE);
		}
		if (IN_ROOM(ch) == IN_ROOM(vict)) {
			GET_POS(vict) = POS_SITTING;
		}
	}
	WAIT_STATE(ch, PULSE_VIOLENCE * 2);
}

ACMD(do_rescue) {
	char arg[MAX_INPUT_LENGTH];
	struct char_data *vict, *tmp_ch;
	int percent, prob;

	if (IS_NPC(ch) || !GET_SKILL(ch, SKILL_RESCUE)) {
		send_to_char(ch, "You have no idea how to do that.\r\n");
		return;
	}

	one_argument(argument, arg);

	if (!(vict = get_char_vis(ch, arg, NULL, FIND_CHAR_ROOM))) {
		send_to_char(ch, "Whom do you want to rescue?\r\n");
		return;
	}
	if (vict == ch) {
		send_to_char(ch, "What about fleeing instead?\r\n");
		return;
	}
	if (FIGHTING(ch) == vict) {
		send_to_char(ch, "How can you rescue someone you are trying to kill?\r\n");
		return;
	}
	for (tmp_ch = world[IN_ROOM(ch)].people; tmp_ch && (FIGHTING(tmp_ch) != vict);
			tmp_ch = tmp_ch->next_in_room);

	if ((FIGHTING(vict) != NULL) && (FIGHTING(ch) == FIGHTING(vict)) && (tmp_ch == NULL)) {
		tmp_ch = FIGHTING(vict);
		if (FIGHTING(tmp_ch) == ch) {
			send_to_char(ch, "You have already rescued %s from %s.\r\n", GET_NAME(vict),
					GET_NAME(FIGHTING(ch)));
			return;
		}
	}

	if (!tmp_ch) {
		act("But nobody is fighting $M!", FALSE, ch, 0, vict, TO_CHAR);
		return;
	}
	if (GET_CLASS(ch) != CLASS_WARRIOR && GET_CLASS(ch) != CLASS_ANTI_PALADIN &&
			GET_CLASS(ch) != CLASS_MONK && GET_CLASS(ch) != CLASS_PALADIN &&
			GET_CLASS(ch) != CLASS_RANGER) {
		send_to_char(ch, "But only true warriors can do this!");
	}
	percent = rand_number(1, 101);	/* 101% is a complete failure */
	prob = GET_SKILL(ch, SKILL_RESCUE);

	if (percent > prob) {
		send_to_char(ch, "You fail the rescue!\r\n");
		return;
	}
	send_to_char(ch, "Banzai!  To the rescue...\r\n");
	act("You are rescued by $N, you are confused!", FALSE, vict, 0, ch, TO_CHAR);
	act("$n heroically rescues $N!", FALSE, ch, 0, vict, TO_NOTVICT);

	if (FIGHTING(vict) == tmp_ch) {
		stop_fighting(vict);
	}
	if (FIGHTING(tmp_ch)) {
		stop_fighting(tmp_ch);
	}
	if (FIGHTING(ch)) {
		stop_fighting(ch);
	}

	set_fighting(ch, tmp_ch);
	set_fighting(tmp_ch, ch);

	WAIT_STATE(vict, 2 * PULSE_VIOLENCE);
}

EVENTFUNC(event_whirlwind) {
	struct char_data *ch, *tch;
	struct mud_event_data *pMudEvent;
	struct list_data *room_list;
	int count;

	/* This is just a dummy check, but we'll do it anyway */
	if (event_obj == NULL) {
		return 0;
	}
	/* For the sake of simplicity, we will place the event data in easily referenced pointers */
	pMudEvent = (struct mud_event_data *) event_obj;
	ch = (struct char_data *) pMudEvent->pStruct;

	/* When using a list, we have to make sure to allocate the list as it uses dynamic memory */
	room_list = create_list();

	/* We search through the "next_in_room", and grab all NPCs and add them to our list */
	for (tch = world[IN_ROOM(ch)].people; tch; tch = tch->next_in_room) {
		if (IS_NPC(tch)) {
			add_to_list(tch, room_list);
		}
	}

	/* If our list is empty or has "0" entries, we free it from memory and close off our event */
	if (room_list->iSize == 0) {
		free_list(room_list);
		send_to_char(ch, "There is no one in the room to whirlwind!\r\n");
		return 0;
	}

	/*
	 * We spit out some ugly color, making use of the new color options, to let the player know
	 * they are performing their whirlwind strike
	 */
	send_to_char(ch, "\t[f313]You deliver a vicious \t[f014]\t[b451]WHIRLWIND!!!\tn\r\n");

	/* Lets grab some a random NPC from the list, and hit() them up */
	for (count = dice(1, 4); count > 0; count--) {
		tch = random_from_list(room_list);
		hit(ch, tch, TYPE_UNDEFINED);
	}

	/* Now that our attack is done, let's free out list */
	free_list(room_list);

	/*
	 * The "return" of the event function is the time until the event is called again. If we return
	 * 0, then the event is freed and removed from the list, but any other numerical response will
	 * be the delay until the next call
	 */
	if (GET_SKILL(ch, SKILL_WHIRLWIND) < rand_number(1, 101)) {
		send_to_char(ch, "You stop spinning.\r\n");
		return 0;
	} else {
		return 1.5 * PASSES_PER_SEC;
	}
}

/*
 * The "Whirlwind" skill is designed to provide a basic understanding of the mud event and list
 * systems.
 */
ACMD(do_whirlwind) {
	if (IS_NPC(ch) || !GET_SKILL(ch, SKILL_WHIRLWIND)) {
		send_to_char(ch, "You have no idea how.\r\n");
		return;
	}

	if (GET_POS(ch) < POS_FIGHTING) {
		send_to_char(ch, "You must be on your feet to perform a whirlwind.\r\n");
		return;
	}

	/*
	 * First thing we do is check to make sure the character is not in the middle of a whirl wind
	 * attack.
	 *
 	 * "char_had_mud_event() will sift through the character's event list to see if an event of type
 	 * "eWHIRLWIND" currently exists.
 	 */
	if (char_has_mud_event(ch, eWHIRLWIND)) {
		send_to_char(ch, "You are already attempting that!\r\n");
		return;
	}

	send_to_char(ch, "You begin to spin rapidly in circles.\r\n");
	act("$n begins to rapidly spin in a circle!", FALSE, ch, 0, 0, TO_ROOM);

	/*
	 * NEW_EVENT() will add a new mud event to the event list of the character. This function below
	 * adds a new event of "eWHIRLWIND", to "ch", and passes "NULL" as additional data. The event
	 * will be called in "3 * PASSES_PER_SEC" or 3 seconds
	 */
	NEW_EVENT(eWHIRLWIND, ch, NULL, 3 * PASSES_PER_SEC);
	WAIT_STATE(ch, PULSE_VIOLENCE * 3);
}

ACMD(do_kick) {
	char arg[MAX_INPUT_LENGTH];
	struct char_data *vict;
	int percent, prob;

	if (IS_NPC(ch) || !GET_SKILL(ch, SKILL_KICK)) {
		send_to_char(ch, "You have no idea how.\r\n");
		return;
	}
	if (IS_MAGE(ch) || IS_NECROMANCER(ch) || IS_CLERIC(ch) || IS_DRUID(ch) || IS_BARD(ch) ||
			IS_THIEF(ch)) {
		send_to_char(ch, "You had better leave all the martial arts to fighters.\r\n");
		return;
	}

	one_argument(argument, arg);

	if (!(vict = get_char_vis(ch, arg, NULL, FIND_CHAR_ROOM))) {
		if (FIGHTING(ch) && IN_ROOM(ch) == IN_ROOM(FIGHTING(ch))) {
			vict = FIGHTING(ch);
		} else {
			send_to_char(ch, "Kick who?\r\n");
			return;
		}
	}
	if (vict == ch) {
		send_to_char(ch, "Are we not funny today...\r\n");
		return;
	}

	if (ROOM_FLAGGED(ch->in_room, ROOM_PEACEFUL)) {
		send_to_char(ch, "This room has a nice peaceful feeling.\r\n");
		return;
	}
	if (!IS_NPC(vict) && !IS_NPC(ch) && !CAN_MURDER(ch, vict)) {
		send_to_char(ch, "Type 'murder' if you want to attack that person.\r\n");
		return;
	}
	if (MOB_FLAGGED(vict, MOB_SHIP) && !MOB_FLAGGED(ch, MOB_SHIP)) {
		send_to_char(ch, "That just is not possible.\r\n");
		return;
	}

	/* 101% is a complete failure */
	percent = ((10 - (compute_armor_class(vict) / 10)) * 2) + rand_number(1, 101);
	prob = GET_SKILL(ch, SKILL_KICK);

	if (percent > prob) {
		damage(ch, vict, 0, SKILL_KICK);
	} else {
		damage(ch, vict, GET_LEVEL(ch) / 2, SKILL_KICK);
	}
	WAIT_STATE(ch, PULSE_VIOLENCE * 3);
}

ACMD(do_punch) {
	char arg[MAX_INPUT_LENGTH];
	struct char_data *vict;
	int percent, prob;
	struct follow_type *k;
	ACMD(do_assist);


	if (IS_MAGE(ch) || IS_NECROMANCER(ch) || IS_CLERIC(ch) || IS_DRUID(ch) || IS_BARD(ch) ||
			IS_THIEF(ch)) {
		send_to_char(ch, "You had better leave all the martial arts to fighters.\r\n");
		return;
	}
	one_argument(argument, arg);
	if (!(vict = get_char_room_vis(ch, arg, NULL))) {
		if (FIGHTING(ch)) {
			vict = FIGHTING(ch);
		} else {
			send_to_char(ch, "Punch who?\r\n");
			return;
		}
	}
	if (vict == ch) {
		send_to_char(ch, "Are we not funny today...\r\n");
		return;
	}
	if (ROOM_FLAGGED(ch->in_room, ROOM_PEACEFUL)) {
		send_to_char(ch, "This room has a nice peaceful feeling.\r\n");
		return;
	}
	if (!IS_NPC(vict) && !IS_NPC(ch) && !CAN_MURDER(ch, vict)) {
		send_to_char(ch, "Type 'murder' if you want to attack that person.\r\n");
		return;
	}
	if (MOB_FLAGGED(vict, MOB_SHIP) && !MOB_FLAGGED(ch, MOB_SHIP)) {
		send_to_char(ch, "That just is not possible.\r\n");
		return;
	}
	/* 101% is a complete failure */
	percent = ((10 - (GET_AC(vict) / 10)) * 2) + rand_number(1, 101);
	prob = GET_SKILL(ch, SKILL_PUNCH);
	if (percent > prob) {
		damage(ch, vict, 0, SKILL_PUNCH);
	} else {
		if ((GET_SIZE(ch) - GET_SIZE(vict)) > -2) {
			damage(ch, vict, 12, SKILL_PUNCH);
			for (k = ch->followers; k; k=k->next) {
				if (PRF_FLAGGED(k->follower, PRF_AUTOASSIST) &&
						(k->follower->in_room == ch->in_room)) {
					do_assist(k->follower, GET_NAME(ch), 0, 0);
				}
			}
			WAIT_STATE(vict, PULSE_VIOLENCE * 2);
		} else {
			damage(ch, vict, 5, SKILL_PUNCH);
			for (k = ch->followers; k; k=k->next) {
				if (PRF_FLAGGED(k->follower, PRF_AUTOASSIST) &&
						(k->follower->in_room == ch->in_room)) {
					do_assist(k->follower, GET_NAME(ch), 0, 0);
				}
			}
			WAIT_STATE(vict, PULSE_VIOLENCE * 2);
		}
	}
	WAIT_STATE(ch, PULSE_VIOLENCE * 3);
}

static char *fire_msg[] = {
	"You do not have anything in your hands to throw.\r\n",
	"You must wield the correct weapon.\r\n",
	"You do not have the right missile type for that weapon.\r\n",
	"You must specify a correct direction.\r\n",
	"You pull your arm back and throw $p.",
	"You take aim and fire $p.",
	"With Herculean might, $n throws $p.",
	"With skill equal to that of William Tell, $n fires $p.",
	"Losing its momentum, $p falls to the ground.",
	"Miraculously, $p returns to $n.",
	"Miraculously, $p returns to you.",
	"\n"
};

extern const char *dirs[];
void fire_in_direction(struct char_data *ch, struct obj_data *obj, int look_type, int distance);

ACMD(do_fire) {
	char arg[MAX_INPUT_LENGTH];
	struct obj_data * obj = GET_EQ(ch, WEAR_WIELD);
	int look_type, distance = 1, fumble = FALSE;
	struct obj_data *obj2 = NULL;

	one_argument(argument, arg);
	if (!*arg || (look_type = search_block(arg, dirs, FALSE)) < 0) {
		send_to_char(ch, fire_msg[3]);
		return;
	}
	if (ROOM_FLAGGED(ch->in_room, ROOM_PEACEFUL)) {
		send_to_char(ch, "Divine intervention prevents you from doing that.\r\n");
		return;
	}
	if (subcmd == SCMD_THROW) {
		obj = GET_EQ(ch, WEAR_DUALWIELD);
		if (!obj) {
			obj = GET_EQ(ch, WEAR_HOLD);
			if (!obj) {
				obj = GET_EQ(ch, WEAR_WIELD);
				if (!obj) {
					send_to_char(ch, fire_msg[0]);
					return;
				} else {
					obj = unequip_char(ch, WEAR_WIELD);
				}
			} else {
				obj = unequip_char(ch, WEAR_HOLD);
			}
		} else {
			obj = unequip_char(ch, WEAR_DUALWIELD);
		}
		if (GET_OBJ_TYPE(obj) == ITEM_MISSILE && GET_OBJ_VAL(obj, 0) == 1) {
			distance = 3;
		} else {
			distance = 1;
		}
	} else {    /* fire, not throw */
		if (!obj || GET_OBJ_TYPE(obj) != ITEM_FIREWEAPON) {
			send_to_char(ch, fire_msg[1]);
			return;
		}
		if (GET_EQ(ch, WEAR_HOLD) || GET_EQ(ch, WEAR_DUALWIELD)) {
			send_to_char(ch, "You need a free hand to fire that.\r\n");
			return;
		}
		for (obj2 = ch->carrying; obj2; obj2 = obj2->next_content) {
			if (GET_OBJ_TYPE(obj2) == ITEM_MISSILE && GET_OBJ_VAL(obj2, 0) == 0) {
				if (((GET_OBJ_VAL(obj2, 3) == 0 || GET_OBJ_VAL(obj2, 3) == 3 ||
						GET_OBJ_VAL(obj2, 3) == 4 || GET_OBJ_VAL(obj2, 3) == 5) &&
						(GET_OBJ_VAL(obj, 3) == 0 || GET_OBJ_VAL(obj, 3) == 3 ||
						GET_OBJ_VAL(obj, 3) == 4 || GET_OBJ_VAL(obj, 3) == 5)) ||
						(GET_OBJ_VAL(obj2, 3) == GET_OBJ_VAL(obj, 3))) {
					break;
				}
			}
		}
		if (!obj2)  {
			send_to_char(ch, fire_msg[2]);
			return;
		}
		obj_from_char(obj2);
		switch (GET_OBJ_VAL(obj, 3)) {
			case 2:
			case 7:
			case 8:
				distance = rand_number(1, 3);
				break;
			case 0:
				distance = rand_number(1, 4);
				break;
			case 1:
			case 4:
				distance = rand_number(1, 5);
				break;
			case 3:
				distance = rand_number(1, 6);
				break;
			case 5:
				distance = rand_number(1, 8);
				break;
			case 6:
				distance = rand_number(1, 7);
				break;
		}
	}
	act(fire_msg[4 + subcmd], FALSE, ch, obj, 0, TO_CHAR);
	act(fire_msg[6 + subcmd], FALSE, ch, obj, 0, TO_ROOM);
	if (subcmd == SCMD_THROW) {
		if (GET_OBJ_VAL(obj, 0) == 1) {
			switch (GET_OBJ_VAL(obj, 3)) {
				case 9:
					if (rand_number(0, 95) > GET_SKILL(ch, SKILL_THROW_DAGGER)) {
						fumble = TRUE;
					}
					break;
				case 10:
					if (rand_number(0, 95) > GET_SKILL(ch, SKILL_THROW_AXE)) {
						fumble = TRUE;
					}
					break;
				case 11:
					if (rand_number(0, 95) > GET_SKILL(ch, SKILL_THROW_BLUDGEONING)) {
						fumble = TRUE;
					}
					break;
				case 12:
					if (rand_number(0, 95) > GET_SKILL(ch, SKILL_THROW_SPEAR)) {
						fumble = TRUE;
					}
					break;
			}
			if (fumble) {
				act("You attempt to throw $p, but fumble with it and drop it instead.", FALSE, ch,
						obj, 0, TO_CHAR);
				act("$n attempts to throw $p, but fumbles with it and drops it instead.", FALSE, ch,
						obj, 0, TO_ROOM);
				obj_to_room(obj, ch->in_room);
				return;
			} else {
				fire_in_direction(ch, obj, look_type, distance);
				WAIT_STATE(ch, PULSE_VIOLENCE);
				return;
			}
		}
		fire_in_direction(ch, obj, look_type, distance);
	} else {
		switch (GET_OBJ_VAL(obj, 3)) {
			case 0:
			case 3:
			case 4:
			case 5:
				if (rand_number(0, 95) > GET_SKILL(ch, SKILL_WIELD_BOW)) {
					fumble = TRUE;
				}
				break;
			case 1:
			case 6:
			case 7:
				if (rand_number(0, 95) > GET_SKILL(ch, SKILL_WIELD_CROSSBOW)) {
					fumble = TRUE;
				}
				break;
			case 2:
				if (rand_number(0, 95) > GET_SKILL(ch, SKILL_WIELD_SLING)) {
					fumble = TRUE;
				}
				break;
			case 8:
				if (rand_number(0, 95) > GET_SKILL(ch, SKILL_WIELD_BLOWGUN)) {
					fumble = TRUE;
				}
			break;
		}
		if (fumble) {
			act("You attempt to fire $p, but fumble with it and drop it instead.", FALSE, ch, obj,
					0, TO_CHAR);
			act("$n attempts to fire $p, but fumbles with it and drops it instead.", FALSE, ch, obj,
					0, TO_ROOM);
			obj_to_room(obj2, ch->in_room);
			return;
		} else {
			fire_in_direction(ch, obj2, look_type, distance);
		}
	}
	WAIT_STATE(ch, PULSE_VIOLENCE);
}

void fire_in_direction(struct char_data *ch, struct obj_data *obj, int dir, int distance) {
	room_vnum temp_room = ch->in_room;
	struct obj_data *obj2 = GET_EQ(ch, WEAR_WIELD);
	struct char_data *vict;
	bool contin = TRUE;		/* Has missile hit someone yet? (true = no) */

	while (contin && EXITN(temp_room, dir) && (distance-- > 0) &&
			!IS_SET(EXITN(temp_room, dir)->exit_info, EX_CLOSED)) {
		temp_room = EXITN(temp_room, dir)->to_room;
		contin = fire_at_char(ch, world[temp_room].people, obj, dir);
	}
	if (OBJ_FLAGGED(obj, ITEM_RETURNING)) {
		act(fire_msg[10], FALSE, ch, obj, 0, TO_CHAR);
		act(fire_msg[9], FALSE, ch, obj, 0, TO_ROOM);
		if ((vict = world[temp_room].people)) {
			act(fire_msg[9], FALSE, ch, obj, vict, TO_VICT);
			act(fire_msg[9], FALSE, ch, obj, vict, TO_NOTVICT);
		}
		if (obj2 && OBJ_FLAGGED(obj2, ITEM_2HANDED)) {
			obj_to_char(obj, ch);
		} else {
			perform_wear(ch, obj, WEAR_HOLD);
		}
	} else {
		obj_to_room(obj, temp_room);
	}
	WAIT_STATE(ch, PULSE_VIOLENCE);
}
