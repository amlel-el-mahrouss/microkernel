/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

.section .text
.align 16
.global sys_putstr

sys_putstr:
	mov 0x60, %l3
	add %l3, %o0, %l3
	ld [%l3], %l5

	mov %i0, %l4
	add %l4, %l0, %l4

	mov %l4, %o0
	mov 0x0b, %o1
	call %l5

	nop

	ret
