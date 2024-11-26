/*
 *	========================================================
 *
 *	MP MicroKernel
 *  Last Edited: 07/05/2023
 *
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _SYS_EXT_H
#define _SYS_EXT_H

#include <sys/sys.h>

#define EXT_NAME_LEN (32U)

struct sys_ext
{
    char e_name[EXT_NAME_LEN]; /* what's his name? */
    bool e_free; /* is it free? */
    bool(*e_open)(void); /* is it open? */
    bool(*e_close)(void); /* is it closed? */
    struct sys_ext* e_next; /* next extension on the list */
};

void sys_load_ext(void);
void sys_unload_ext(void);
int32_t sys_load_ext_by_name(const char* name);
int32_t sys_unload_ext_by_name(const char* name);
bool sys_init_root_extension(const char* name, bool(*open)(void), bool(*close)(void));
bool sys_add_ext_by_name(const char* name, bool(*openfn)(void), bool(*closefn)(void));

#endif //!_SYS_EXT_H
