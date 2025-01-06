/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 28/04/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * ========================================================
 */

#ifndef _MP_ENVVAR_H
#define _MP_ENVVAR_H

#include <sys/sys.h>
#include <sys/malloc.h>

bool  sys_init_env(void);
char* sys_get_env(const char* name);
int   sys_set_env(const char* name, const char* value);

#endif /* ifndef _MP_ENVVAR_H */
