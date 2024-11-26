/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <hw/pci_express.h>
#include <hw/mmap.h>

__COPYRIGHT("$kernel$");

/* RedHat PCIe Host Bridge */
#define SYS_PCI_HOST_RH  0x81b36
#define SYS_PCI_HOST_INTL 0x8086

const char* hw_get_pcie_host(uint32_t host)
{
    switch (host)
    {
    case SYS_PCI_HOST_RH:
        return "RedHat PCIe Host Bridge\r\n";
    case SYS_PCI_HOST_INTL:
        return "Intel PCIe Host Bridge\r\n";
    default:
        return "Unknown PCIe Host Bridge\r\n";
    }

    return "?";
}

uintptr_t hw_get_pcie_address_ptr(void)
{
    return sys_get_mmap()[HW_MEMMAP_PCIE_ECAM].base_ptr;
}

size_t hw_get_pcie_address_size(void)
{
    return sys_get_mmap()[HW_MEMMAP_PCIE_ECAM].length_ptr;
}
