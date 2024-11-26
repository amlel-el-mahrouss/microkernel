/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <sched/sched.h>

struct sys_process_info
{
    char             p_name[SCHED_NAME_LEN];
    struct sys_sdctl p_sdctl;
    struct sys_thread* p_thread;
};

struct sys_process_info sys_sched_get_current_info(void);

typedef struct sys_process_info process_info_t;
