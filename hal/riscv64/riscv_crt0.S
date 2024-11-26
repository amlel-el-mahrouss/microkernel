/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

.section .init
.align 4

.extern mach_start_sched_smp
.extern __mach_go_hang
.extern mach_start

.option norvc

.global mach_smp_init
.global __mach_start
.global __sys_hart_present

__mach_start:
	.cfi_startproc

.option push
.option norelax

	la gp, __sys_global_pointer

.option pop

	la sp, __sys_stack_end

	la t5, _bss_start
	la t6, _bss_end

__crt0_bss_clear:
	sd zero, (t5)
	addi t5, t5, 8
	bgeu t5, t6, __crt0_bss_clear

	mv t1, zero
	csrr t0, mhartid
	addi t1, zero, 1

	beqz t0, __mach_start_hart0
	beq t0, t1, __mach_smp_start_hart1

	j __mach_go_hang

	.cfi_endproc

__mach_smp_start_hart1:
	la sp, __sys_second_stack_end
	j mach_start_sched_smp
	ret

__mach_start_hart0:
	j mach_start
	ret

.section .bss
.align 4

__sys_hart_present:
	.long 0
