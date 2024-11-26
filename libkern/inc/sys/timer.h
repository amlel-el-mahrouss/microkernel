/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __SYS_TIMER_H__
#define __SYS_TIMER_H__

#include <sys/sys.h>

// 1000 Hz
#define SYS_TIMER_INTERVAL (0x1000000)

/* timer delay */
typedef uintptr_t duration_t;

// initialize the timer
void sys_timer_init(void);

// sleep until 'ms = 0'
void sys_sleep_for(duration_t ms);
const duration_t sys_get_time(void);

#endif // !__SYS_TIMER_H__
