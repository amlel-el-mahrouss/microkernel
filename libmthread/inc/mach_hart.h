/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <sys/sys.h>
#include <sched/sched.h>

void __mach_switch_hart(int id, struct sched_snapshot* snap);
int32_t __mach_hart_get(void);
