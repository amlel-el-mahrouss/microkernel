/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

.global __mach_start
.extern __mach_start

.set noreorder

.set __STACK_SIZE, 0x1000

.section .text

__mach_start:
	la $sp, stack
	addiu $sp, __STACK_SIZE - 32
	jal mach_start
	nop
	b .
	nop

.section .bss
stack:
	.space STACKSIZE
