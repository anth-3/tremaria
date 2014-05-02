/***************************************************************************************************
*                                                                   Part of the Realms of Tremaria *
* File: bsd-snprintf.h                                                          A CircleMUD/tbaMUD *
* Description: Used if your OS does not provide snprintf() or vsnprintf().                         *
*                                                                                                  *
* All rights reserved.  See license for complete information.                                      *
*                                                                                                  *
* Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University                           *
* CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.                                         *
* Last updated: 16 April 2014 -- anth*3                                                            *
***************************************************************************************************/
/* This file taken from openbsd-compat of OpenSSH 3.1:
 *
 * --- 8< --- OpenSSH LICENSE --- 8< ---
 * Remaining components of the software are provided under a standard
 * 2-term BSD licence with the following names as copyright holders:
 *
 *      Markus Friedl
 *      Theo de Raadt
 *      Niels Provos
 *      Dug Song
 *      Aaron Campbell
 *      Damien Miller
 *      Kevin Steves
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --- 8< --- OpenSSH LICENSE --- 8< ---
 */

#ifndef __BSD_SNPRINTF_H__
#define __BSD_SNPRINTF_H__

#ifndef HAVE_SNPRINTF
int snprintf(char *str, size_t count, const char *fmt, ...);
#endif /* !HAVE_SNPRINTF */

#ifndef HAVE_VSNPRINTF
int vsnprintf(char *str, size_t count, const char *fmt, va_list args);
#endif /* !HAVE_SNPRINTF */

#endif /* __BSD_SNPRINTF_H__ */
