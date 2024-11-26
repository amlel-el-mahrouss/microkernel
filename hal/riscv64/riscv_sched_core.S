/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include "riscv.inc"

/* scheduler helpers */

.globl sys_sched_switch_context

# sys_sched_switch_context(stack* dest, stack* src)
.align 4
sys_sched_switch_context:
	sd ra, 0(a0)
	sd sp, 8(a0)
	sd s0, 16(a0)
	sd s1, 24(a0)
	sd s2, 32(a0)
	sd s3, 40(a0)
	sd s4, 48(a0)
	sd s5, 56(a0)
	sd s6, 64(a0)
	sd s7, 72(a0)
	sd s8, 80(a0)
	sd s9, 88(a0)
	sd s10, 96(a0)
	sd s11, 104(a0)

	csrr t0, satp
	ld t0, 112(a0)

	csrr t1, ustatus
	ld t1, 120(a0)

	csrr t2, uepc
	ld t2, 128(a0)

	ld ra, 0(a1)
	ld sp, 8(a1)
	ld s0, 16(a1)
	ld s1, 24(a1)
	ld s2, 32(a1)
	ld s3, 40(a1)
	ld s4, 48(a1)
	ld s5, 56(a1)
	ld s6, 64(a1)
	ld s7, 72(a1)
	ld s8, 80(a1)
	ld s9, 88(a1)
	ld s10, 96(a1)
	ld s11, 104(a1)

	ld t0, 112(a1)
    csrw satp, t0

	ld t1, 120(a1)
    csrw ustatus, t1

	ld t2, 128(a1)
    csrw uepc, t2

    mv t2, ra

    uret
