/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <hw/mmu.h>
#include <hw/cpu.h>

__COPYRIGHT("$kernel$");

void sys_set_satp(voidptr_t pool_ptr, prot_t prot)
{
    if (pool_ptr == null)
        return;

    uintptr_t satp = SATP_MODE_SV48 | (((uintptr_t)pool_ptr) >> 12) | prot;
    sys_write_satp(satp);
}

uintptr_t sys_get_satp(void)
{
    return sys_read_satp();
}
