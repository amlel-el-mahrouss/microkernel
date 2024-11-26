/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <smp.h>
#include <kernel.h>
#include <stdio.h>
#include <sys/log.h>
#include <stdlib.h>
#include <hw/cpu.h>
#include <hw/uart.h>
#include <hw/trap.h>
#include <sys/timer.h>
#include <sys/mman.h>
#include <sched/sched.h>
#include <machine/exec.h>

// init helper
#define try_init_feature(EXPR, ERR)\
    if (!(EXPR))\
    {\
        sys_print_format(ERR);\
    }




/* mach procedure, hal to kernel layer. */
int mach_start(void)
{
    while (sys_read_hart_id() >= 2) {}

    try_init_feature(sys_init_trap_system(), "[TRAPS] Init failure... Booting halted.\r\n");

    // TODO: handle mpp correctly.
    sys_timer_init();

    sys_print_format("[smp] hart %i\n", sys_read_hart_id());

    sys_init_kernel();

    return 0;
}

#undef try_init_feature
