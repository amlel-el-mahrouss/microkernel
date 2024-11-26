/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <hw/mmap.h>
#include <hw/mmu.h>

__COPYRIGHT("$kernel$");

// @file riscv_mmap.c
// @brief riscv memory layout.

struct sys_hw_memmap g_riscv_memmap[] = {
    [0] = { .base_ptr = 0x0, .length_ptr = 0x100, .feature_set = 0 }, // debug
    [1] = { .base_ptr = 0x100, .length_ptr = 0x11000, .feature_set = 0 }, // mrom
    [2] = { .base_ptr = 0x100000, .length_ptr  = 0x1000, .feature_set = HW_FEATURE_POWER_MANAGER }, // resr
    [3] = { .base_ptr = 0x2000000, .length_ptr = 0x10000, .feature_set = 0 }, // clint
    [4] = { .base_ptr = 0x0c000000, .length_ptr  = 0x4000, .feature_set = 0 }, // plic
    [5] = { .base_ptr = 0x10000000, .length_ptr = 0x100, .feature_set = 0 }, // uart
    [6] = { .base_ptr = 0x10001000, .length_ptr = 0x1000, .feature_set = HW_FEATURE_VIRT_BLK }, // virtio block device
    [7] = { .base_ptr = 0x80000000, .length_ptr = 0x0, .feature_set = 0 }, // dram
    [8] = { .base_ptr = 0x40000000, .length_ptr = 0x40000000, .feature_set = 0 }, // pcie mmio
    [9] = { .base_ptr = 0x03000000, .length_ptr = 0x00010000, .feature_set = 0 }, // pcie pio
    [10] = { .base_ptr = 0x30000000, .length_ptr = 0x10000000, .feature_set = 0 }, // pcie ecam
    [11] = { .base_ptr = 0x101000, .length_ptr = 0x1000, .feature_set = 0 }, // real time clock
    [12] = { .base_ptr = 0x00008000, .length_ptr = 0x0000bfff, .feature_set = HW_FEATURE_VGA }, // video graphics array
    [13] = { .base_ptr = 0x00001000, .length_ptr = 0x1000, .feature_set = HW_FEATURE_VIRT_NET }, // virtio block device
    [14] = { .base_ptr = 0x90000000, .length_ptr = 0x1000, .feature_set = HW_FEATURE_PCI_TREE }, // virtio block device
};

struct sys_hw_memmap* sys_get_mmap(void) { return g_riscv_memmap; }

static bool sys_pte_is_taken(struct sys_page_table_entry* pte) { return pte->gran & (1 << 0); }

static struct sys_page_table_entry* sys_pte_add(struct sys_page_table_entry* pte, size_t amount, uint16_t map_flags)
{
    pte = pte + (sizeof(struct sys_page_table_entry) * amount);

    if (map_flags & SYS_MAP_SHARED)
    {
        pte->gran |= map_flags & SYS_PROT_WRITE ? RISCV_PERM_WRITE : 0;
        pte->gran |= map_flags & SYS_PROT_READ ? RISCV_PERM_READ : 0;
        pte->gran |= map_flags & SYS_PROT_EXEC ? RISCV_PERM_EXEC : 0;
    }

    return pte;
}

voidptr_t sys_map_memory(voidptr_t paddr, int32_t map_flags, size_t length)
{
    struct sys_page_table_entry* pte = (struct sys_page_table_entry*)paddr;

    const int32_t heap_size = __sys_memory_end - __sys_heap_start;
    const size_t num_pages = heap_size / __PAGE_SIZE__;

    for (size_t index = 0UL; index < num_pages - length; ++index)
    {
        for (size_t page_index = 0UL; page_index < index + length; ++page_index)
        {
            if (sys_pte_is_taken(sys_pte_add(pte, page_index, map_flags)))
                return null;

            break;
        }
    }

    // find MMU entry, and set entry.

    return (voidptr_t)paddr;
}

int32_t sys_unmap_memory(voidptr_t paddr, size_t length)
{
    return 0;
}
