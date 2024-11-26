/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __SYS_KERNEL_H__
#define __SYS_KERNEL_H__

#include <sys/log.h>
#include <kernel.h>
#include <sys/fd.h>
#include <hw/mmap.h>
#include <sys/sys.h>
#include <sys/ext.h>
#include <sys/cstr.h>
#include <sys/utils.h>
#include <sys/malloc.h>
#include <sched/sched.h>
#include <sched/helper.h>

int sys_init_kernel(void);

extern const gid_t g_kgid;
extern uid_t g_kuid;

#endif // !__SYS_KERNEL_H__
