/***************************************************************************************************
*                                                                   Part of the Realms of Tremaria *
* File: ban.h                                                                   A CircleMUD/tbaMUD *
* Description: Header file for banning/unbanning/checking sites and player names (ban.c).          *
*                                                                                                  *
* All rights reserved.  See license for complete information.                                      *
*                                                                                                  *
* Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University                           *
* CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.                                         *
* Last updated: 30 March 2014 -- anth*3                                                            *
***************************************************************************************************/

#ifndef __BAN_H__
#define __BAN_H__

/* don't change these */
#define BAN_NOT 	0
#define BAN_NEW 	1
#define BAN_SELECT 	2
#define BAN_ALL 	3

#define BANNED_SITE_LENGTH 	50
struct ban_list_element {
	char 	site[BANNED_SITE_LENGTH+1];
	int 	type;
	time_t 	date;
	char 	name[MAX_NAME_LENGTH+1];
	struct 	ban_list_element *next;
};

/* Global functions */
/* Utility Functions */
void load_banned(void);
int isbanned(char *hostname);
int valid_name(char *newname);
void read_invalid_list(void);
void free_invalid_list(void);
/* Command functions without subcommands */
ACMD(do_ban);
ACMD(do_unban);

/* Global buffering */
#ifndef __BAN_C__

extern struct ban_list_element *ban_list;
extern int num_invalid;
extern mob_rnum top_of_mobt;
extern struct char_data *mob_proto;

#endif /*__BAN_C__ */

#endif /* __BAN_H__ */
