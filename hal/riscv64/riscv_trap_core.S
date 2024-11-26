/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include "riscv.inc"

.extern sys_trap_handler

.globl sys_trap_vector

sys_trap_vector:
    csrrw t6, mscratch, t6
    sys_reg_save t6
    csrw mscratch, t6

    j sys_trap_handler

    csrw mepc, a0

    csrr t6, mscratch
    sys_reg_load t6
    ret
