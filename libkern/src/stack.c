/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sched/sched.h>
#include <sys/sys.h>
#include <errno.h>

unsigned long __stack_chk_guard = 0UL;

void __stack_chk_fail(void)
{
    IOLog("[stack] canary violation!\r\n");
    panic("stack_canary_failure\r\n");

    mpux_no_reach();
}
