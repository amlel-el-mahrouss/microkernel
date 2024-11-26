/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/sys.h>

extern int64_t __sys_hart_present;

void __mach_increment_hart(void)
{
    ++__sys_hart_present;
}
