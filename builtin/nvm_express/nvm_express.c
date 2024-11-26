/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 10/11/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <nvm_express/nvm_express.h>
#include <fs/types.h>
#include <fs/quota.h>
#include <hw/pci.h>
#include <sys/dev.h>
#include <string.h>

__COPYRIGHT("$kernel$");

#define NVME_CLASS_CODE    0x01
#define NVME_SUBLCASS_CODE 0x08

#define NVME_BAR_VERSION_0 0x08
#define NVME_BAR_VERSION_1 0x0B

#define NVME_BAR_INTMASK_0 0x0C
#define NVME_BAR_INTMASK_1 0x0F

#define NVME_BAR_INTMC_0 0x10
#define NVME_BAR_INTMC_1 0x13

#define NVME_BAR_CC_0 0x14
#define NVME_BAR_CC_1 0x17

#define NVME_BAR_CSTS_0 0x1C
#define NVME_BAR_CSTS_1 0x1F

#define NVME_BAR_AQA_0 0x24
#define NVME_BAR_AQA_1 0x27

#define NVME_BAR_ASQ_0 0x28
#define NVME_BAR_ASQ_1 0x2F

#define NVME_BAR_ACQ_0 0x30
#define NVME_BAR_ACQ_1 0x37

/**
 * @brief Ring Doorbell offset
 */

#define NVME_BAR_SQxTDBL(X, Y)  (0x1000 + (X) * Y)

/**
 * @brief Command Queue offset
 */

#define NVME_BAR_CQxHDBL(X, Y)  (0x1000 + ( X + 1 ) * Y)

#define NVME_CREATE_SUBQUEUE    0x01
#define NVME_COMPLETION_QUEUE   0x05

#define NVME_IDENTIFY           0x06

#define NVME_READ               0x02
#define NVME_WRITE              0x01

#define NVME_MAX_DRIVES         4

#define _MPUX_NVME_PROC_IO(n) int32_t __nvme_dev##n(pipe_t* pipe)
#define _MPUX_NVME_PROC_IO_STAT(n) _MPUX_NVME_PROC_IO(n)

static void hw_nvme_init_internal(void);

typedef uintptr_t nsid_t;
typedef uintptr_t nscap_t;
typedef uintptr_t nssz_t;
typedef uintptr_t nsutil_t;
typedef uintptr_t bar_t;

static struct sys_dev*      g_dev = nil;

/////////////////////////////////////////////////////////////////////////////////

// @file nvm_express.c
// @brief NVME support

/////////////////////////////////////////////////////////////////////////////////

struct nvme_device_info
{
    bar_t b_bar; /* base address register */
    nscap_t b_caps; /* capabilities */
    nsid_t b_nsid; /* namespace id */
    nsutil_t b_nsu; /* namespace utilization */
    nssz_t b_sz; /* namespace size */
    int16_t b_mag; /* magic ready bit */
};

static struct nvme_device_info __attribute__((unused))
    g_nvme_drives[NVME_MAX_DRIVES] = { { 0 } };

static struct hw_pci_tree* g_nvme_pci_tree = null;

static struct nvme_device_info* __attribute__((unused)) g_nvme_active = nil;

static struct fs_quota __attribute__((unused))
    g_nvme_quotas[NVME_MAX_DRIVES] = {
    {
        .num_users = 0,
        .users = nil,
    },
    {
        .num_users = 0,
        .users = nil,
    },
    {
        .num_users = 0,
        .users = nil,
    },
    {
        .num_users = 0,
        .users = nil,
    },
};

/* @brief this one checks disk quota, user should abort any operations if quota is bigger or equal to 100. */
_MPUX_NVME_PROC_IO_STAT(_disk_quota_check)
{
    (void)pipe;

    for (size_t i = 0; i < NVME_MAX_DRIVES; i++)
    {
        if (sys_quota_check(&g_nvme_quotas[i]) >= 100)
        {
            return i;
        }
    }

    return -1;
}

#define NVME_READY_BIT 0x4775

/**
 * @brief Called when device submits an external interrupt to the OS.
 */

void nvme_drive_ready_interrupt(void)
{
    if (g_nvme_active)
    {
        if (g_nvme_active->b_mag == NVME_READY_BIT)
        {
            /* driver is ready to serve buffer. */
            g_nvme_active->b_mag = 0;
        }
    }
}

#define NVME_CMD_READ 0
#define NVME_CMD_WRITE 1
#define NVME_CMD_FORMAT 2
#define NVME_CMD_EJECT 3

/// @brief init hardware: nvme driver
/// @param void this function takes no parameters.
void hw_nvme_init(void)
{
    // function map
    // 0 - read
    // 1 - write
    // 2 - format
    // 3 - eject

    struct sys_hw_memmap* mmap = sys_get_mmap();

    if (mmap != nil)
    {
        IOLog("[nvme] disk: start probe for disks...\n");

        struct hw_pci_tree* tree_ptr = (struct hw_pci_tree*)mmap[HW_MEMAMP_PCI_TREE].base_ptr;

        // search a valid BAR using the pci tree.
        if (tree_ptr->d_magic == SYS_PCI_DEV_MAGIC)
        {
            struct hw_pci_tree* start = tree_ptr;

            while (start != null)
            {
                struct hw_pci_tree* sub_level_start = start;

                while (sub_level_start != null)
                {
                    if (*sub_level_start->d_name != 0)
                    {
                        IOLog("[nvme] Identify device if /ndisk...\n");

                        // /ndisk = nvm disk, we omit the rest, it's just an id for it.
                        if (strncmp(sub_level_start->d_name, "/ndisk", strlen("/ndisk")) == 0)
                        {
                            IOLog("[nvme] Device is 'ndisk', stop here.");

                            g_nvme_pci_tree = sub_level_start;

                            g_dev = sys_make_dev(
                                "/dev/nvm1",
                                strlen("/dev/nvm1"),
                                4
                            );

                            // we're done probing, initialize device now.
                            return hw_nvme_init_internal();
                        }
                    }

                    // if it fails, jump to next sibling.
                    sub_level_start = (struct hw_pci_tree *)sub_level_start->d_next_sibling;
                }

                // if it fails, get the next first node of this tree.
                start = (struct hw_pci_tree *)start->d_first_node;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////

// Command assembler for NVME.

/////////////////////////////////////////////////////////////////////////////////////

#define NVME_OPCODE_FEATURE_IDENT       0x0b
#define NVME_OPCODE_DEVICE_SELF_TEST    0x06

//////////////////////////////////////////////////////////////////////////

/// @brief Setup the disk to process commands.
/// @param void
/// @return nothing.

//////////////////////////////////////////////////////////////////////////

static void hw_nvme_init_internal(void)
{

}
