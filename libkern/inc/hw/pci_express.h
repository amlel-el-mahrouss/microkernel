/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MPUX_PCI_EXPRESS_H
#define _MPUX_PCI_EXPRESS_H

///////////////////////////////////////////////////////////////////

// @brief PCI implementation and it's tree.

///////////////////////////////////////////////////////////////////

#include <sys/sys.h>

#define PCI_INVALID_DATA_U8     ((uint8_t)~0)
#define PCI_INVALID_DATA_U16    ((uint16_t)~0)
#define PCI_INVALID_DATA_U32    ((uint32_t)~0)

#define PCI_CONFIG_SPACE        (4096U)

#define PCI_BUS_MAX             (256U)
#define PCI_DEV_MAX             (32U)
#define PCI_FN_MAX              (8U)

#define SYS_PCI_DEV_MAGIC 0xfeedd00d
#define SYS_PCI_INT_SZ    sizeof(pci_num_t)

typedef char      pci_char_t;
typedef uintptr_t pci_num_t;

typedef uint8_t pci_fn_t;
typedef uint8_t pci_bus_t;
typedef uint8_t pci_device_t;

const char* hw_get_pcie_host(uint32_t host);

size_t hw_get_pcie_address_size(void);
uintptr_t hw_get_pcie_address_ptr(void);

/// @brief hardware tree header
/// used by device drivers.
struct hw_pci_tree
{
    pci_num_t d_magic;
    pci_num_t d_version;
    pci_num_t d_off_props;
    pci_num_t d_off_struct;
    pci_num_t d_sz_props;
    pci_num_t d_sz_struct;

    pci_num_t d_first_node;
    pci_num_t d_next_sibling;

    pci_char_t d_name[];
};

#endif // ifndef _MPUX_PCI_EXPRESS_H
