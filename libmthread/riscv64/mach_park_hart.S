/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

.globl __mach_park_thrd
.align 4

__mach_park_thrd:
	wfi
	j __mach_park_thrd
