/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <mach_hart.h>

int32_t __mach_hart_get(void)
{
	return sys_read_hart_id();
}

// __mach_switch_hart, doesn't switch for a specific hart.
// but waits for that hart to execute code.
// this will be used for inter-process-communication and scheduling.

// the __mach_switch_hart is defined in <your_chosen_arch>/mach_hart_asm.S
