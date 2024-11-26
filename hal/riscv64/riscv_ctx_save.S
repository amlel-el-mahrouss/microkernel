/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include "riscv.inc"

.globl sys_sched_save_context
.align 4
sys_sched_save_context:
    sys_reg_save a0
    ret
