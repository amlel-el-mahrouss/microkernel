/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

.section .text
.global _start
.align 16

_start:
.1:
	call .1
	mov %o7, %l0

	mov _sys_splash - _start, %i0
	call sys_putstr

.2:
	call .2
	nop

_sys_splash:
	.string "MultiProcessor UNIX"
