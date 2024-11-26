/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

.globl sys_tlb_flush
.align 4

sys_tlb_flush:
    csrr a0, satp
    sfence.vma

    ret

.global sys_tlb_set
.align 4

sys_tlb_set:
    csrr t0, satp
    mv a1, t0
    csrw satp, a0
    ret
