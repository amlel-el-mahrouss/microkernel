/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

.globl __mach_switch_hart
.align 4

.globl g_mach_current_snap

__mach_switch_hart:
	csrr t0, mhartid
	beq t0, a0, L1
	ret

L1:
	ld t1, g_mach_current_snap
	mv t1, a1

	ret


.globl __mach_set_context
.align 4

__mach_set_context:
	ld ra, 0(a0)
	ld sp, 8(a0)
	ld s0, 16(a0)
	ld s1, 24(a0)
	ld s2, 32(a0)
	ld s3, 40(a0)
	ld s4, 48(a0)
	ld s5, 56(a0)
	ld s6, 64(a0)
	ld s7, 72(a0)
	ld s8, 80(a0)
	ld s9, 88(a0)
	ld s10, 96(a0)
	ld s11, 104(a0)

	csrr t0, satp
	ld t0, 112(a0)

	ret
