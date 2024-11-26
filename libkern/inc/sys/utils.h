/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __SYS_UTILS_H__
#define __SYS_UTILS_H__

#include <sys/sys.h>
#include <sched/sched.h>

/* scheduler helpers */
struct sched_snapshot* make_sched_snapshot(reg_t ra, reg_t sp);

/* character helpers */
int32_t sys_is_alnum(int32_t c);
int32_t sys_is_ctrl(int32_t c);

#endif //!__SYS_UTILS_H__
