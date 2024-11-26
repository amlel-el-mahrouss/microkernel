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

static bool pte_is_taken(struct sys_page_table_entry* pte) { return pte->gran & (1 << 0); }
static bool pte_is_last(struct sys_page_table_entry* pte) { return pte->gran & (1 << 1); }
static void pte_clear(struct sys_page_table_entry* pte) { pte->gran = 0; }

#define RISCV_VPN0_SHIFT 12
#define RISCV_VPN1_SHIFT 21
#define RISCV_VPN2_SHIFT 30

#define RISCV_VPN0(va) ((((uintptr_t)(va)) >> RISCV_VPN0_SHIFT) & 0x01FF)
#define RISCV_VPN1(va) ((((uintptr_t)(va)) >> RISCV_VPN1_SHIFT) & 0x01FF)
#define RISCV_VPN2(va) ((((uintptr_t)(va)) >> RISCV_VPN2_SHIFT) & 0x01FF)

static struct sys_page_table_entry* pte_add(struct sys_page_table_entry* pte, size_t amount,
                                            prot_t prot, int32_t map)
{
    pte = pte + (sizeof(struct sys_page_table_entry) * amount);

    return pte;
}

voidptr_t sys_alloc_memory(voidptr_t paddr, size_t length, prot_t prot, int32_t map)
{
    uintptr_t addr = (uintptr_t)paddr + __sys_heap_start / __PAGE_SIZE__;
    struct sys_page_table_entry* pte = (struct sys_page_table_entry*)addr;

    const int32_t heap_size = __sys_memory_end - __sys_heap_start;
    const size_t num_pages = heap_size / __PAGE_SIZE__;

    for (size_t index = 0UL; index < (num_pages - length); ++index)
    {
        for (size_t page_index = 0UL; page_index < (index + length); ++page_index)
        {
            pte = pte_add(pte, page_index, prot, map);

            if (pte_is_taken(pte))
                continue;

            break;
        }
    }

    return (voidptr_t)pte;
}

int32_t sys_delete_memory(voidptr_t paddr, size_t length)
{
    /* we actually don't care about that, just ignore it. */
    (void)length;

    if (paddr == null) return -1;

    uintptr_t addr = (uintptr_t)paddr + __sys_heap_start / __PAGE_SIZE__;
    struct sys_page_table_entry* pg = (struct sys_page_table_entry*)addr;

    while (pte_is_taken(pg) && !pte_is_last(pg))
    {
        pte_clear(pg);
        pg = pte_add(pg, 1, 0, 0);
    }

    pte_clear(pg);

    return 0;
}

const uintptr_t sys_heap_start(void)
{
    return __sys_heap_start;
}
