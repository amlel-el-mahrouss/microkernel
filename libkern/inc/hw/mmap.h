/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __SYS_MEMMAP_H__
#define __SYS_MEMMAP_H__

#include <sys/sys.h>

#ifdef __SYS_RISCV__

struct sys_hw_memmap
{
    uintptr_t base_ptr;
    size_t length_ptr;
    int32_t feature_set;
};

enum
{
    HW_MEMMAP_DEBUG,
    HW_MEMMAP_MROM,
    HW_MEMMAP_RESR,
    HW_MEMMAP_CLINT,
    HW_MEMMAP_PLIC,
    HW_MEMMAP_UART,
    HW_MEMMAP_VIRT_BLK,
    HW_MEMMAP_DRAM,
    HW_MEMMAP_PCIE_MMIO,
    HW_MEMMAP_PCIE_PIO,
    HW_MEMMAP_PCIE_ECAM,
    HW_MEMMAP_RTC,
    HW_MEMMAP_PVC, // platform video controller
    HW_MEMMAP_VIRT_NET, // platform video controller
    HW_MEMAMP_PCI_TREE, // pci device tree.
    HW_MEMMAP_COUNT,
};

struct sys_hw_memmap* sys_get_mmap(void);

#endif

#define HW_FEATURE_VGA           10
#define HW_FEATURE_HDMI          11
#define HW_FEATURE_VIRT_BLK      12
#define HW_FEATURE_VIRT_NET      13
#define HW_FEATURE_POWER_MANAGER 14
#define HW_FEATURE_PCI_TREE      15

voidptr_t sys_map_memory(voidptr_t paddr, int32_t map_flags, size_t length);
int32_t sys_unmap_memory(voidptr_t paddr, size_t length);

#endif // !__SYS_MEMMAP_H__
