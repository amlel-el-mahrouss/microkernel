/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <hw/cpu.h>


///////////////////////////////////////////////////////////////////////

/* @brief RISC-V register manip */

///////////////////////////////////////////////////////////////////////

reg_t sys_read_hart_id(void)
{
	reg_t reg = 0UL;
	asm volatile("csrr %0, mhartid" : "=r" (reg) );
	return reg;
}

reg_t sys_read_mstatus(void)
{
    reg_t reg = 0UL;
    asm volatile("csrr %0, mstatus" : "=r" (reg) );
    return reg;
}

void sys_write_mstatus(reg_t reg)
{
    asm volatile("csrw mstatus, %0" : : "r" (reg));
}

void sys_write_mepc(reg_t reg)
{
    asm volatile("csrw mepc, %0" : : "r" (reg));
}

void sys_write_satp(reg_t reg)
{
    asm volatile("csrw satp, %0" : : "r" (reg));
}

reg_t sys_read_satp(void)
{
    reg_t reg = 0UL;
    asm volatile("csrr %0, mepc" : "=r" (reg));

    return reg;
}

reg_t sys_read_mepc(void)
{
    reg_t reg = 0UL;
    asm volatile("csrr %0, mepc" : "=r" (reg));

    return reg;
}

void sys_write_mscratch(reg_t reg)
{
    asm volatile("csrw mscratch, %0" : : "r" (reg));
}

void sys_write_mtvec(reg_t reg)
{
    asm volatile("csrw mtvec, %0" : : "r" (reg));
}

reg_t sys_read_mie(void)
{
    reg_t reg = 0UL;
    asm volatile("csrr %0, mie" : "=r" (reg) );

    return reg;
}

void sys_write_mie(reg_t reg)
{
    asm volatile("csrw mie, %0" : : "r" (reg));
}

reg_t sys_read_mcause(void)
{
    reg_t reg = 0UL;
    asm volatile("csrr %0, mcause" : "=r" (reg) );
    return reg;
}

reg_t sys_read_scause(void)
{
    reg_t reg = 0UL;
    asm volatile("csrr %0, scause" : "=r" (reg) );
    return reg;
}

reg_t sys_read_sepc(void)
{
    reg_t reg = 0UL;
    asm volatile("csrr %0, sepc" : "=r" (reg) );
    return reg;
}
