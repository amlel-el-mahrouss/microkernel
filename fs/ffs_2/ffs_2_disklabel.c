/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <ffs_2/disklabel.h>
#include <sys/timer.h>
#include <sys/malloc.h>
#include <sys/dev.h>
#include <string.h>
#include <oseek.h>
#include <lseek.h>
#include <pfs.h>

/**
 * The ffs2 disklabels starts after the kernel partiion map block.
 * MBS is a partition scheme used by the kernel to know where to boot a system.
 */

#include <fs/partition_map.h>

#define FFS_2_BASE_LABEL_TABLE (sizeof(struct boot_block) * MBS_MAX_BLKS)
#define FFS_2_END_OF_BLT       (FFS_2_BASE_LABEL_TABLE + sizeof(struct ffs_2_disklabel) * MAX_MAX_PARTS)

/**
 * @brief A device tree to probe for a filesystem.
 * @author Amlal EL Mahrouss
 */

static bool g_device_found = false;

struct sys_ffs_device_tree g_device_tree[] = {
    {
        .dev_name = "/dev/sd1",
        .dev_len = 10,
    },
    {
        .dev_name = "/dev/sd2",
        .dev_len = 10,
    },
    {
        .dev_name = "/dev/sd3",
        .dev_len = 10,
    },
    {
        .dev_name = "/dev/nvm1",
        .dev_len = 10,
    },
    {
        .dev_name = "/dev/nvm2",
        .dev_len = 10,
    },
    {
        .dev_name = "/dev/nvm3",
        .dev_len = 10,
    },
    {
        .dev_name = "/dev/vdk0",
        .dev_len = 10,
    }
};

/**
 * @brief Initialize a disk label from a mountable device.
 *
 * @param dlabel the disklabel in person.
 * @return true the disk is here and has a disklabel on it.
 * @return false not a disk or doesn't have a diskabel on it.
 */

static bool ffs_2_disklabel_init(struct ffs_2_disklabel* dlabel)
{
    if (g_device_found)
        return false;

    uintptr_t* indexes = sys_dev_find_tree("/dev/");

    /* do some probing... */
    for (size_t device_tree_index = 0; device_tree_index < FFS_DEV_TREE_LEN; ++device_tree_index)
    {
        sys_print_format("[ffs_2] trying to format %s\r\n", g_device_tree[device_tree_index].dev_name);

        /* probe device using an offset */
        for (size_t device_index = 0; device_index < DEV_ARR_LEN; device_index++)
        {
            if (indexes[device_index] == 0)
                break;

            dev_t* dev = (dev_t*)indexes[device_index];

            if (dev == null)
                continue;

            while (dev->state == DEV_STATUS_BUSY)
            {
                sys_sleep_for(500);
                sys_print_format("[ffs_2] waiting for device unlock: %s\r\n", dev->name);
            }

            if (strncmp(dev->name, g_device_tree[device_tree_index].dev_name, strlen(dev->name)) == 0)
            {
                dev->state = DEV_STATUS_BUSY;

                sys_print_format("[ffs_2] reading %s\r\n", dev->name);

                buf_t* buf_pipe = sys_make_buffer(sys_alloc_ptr(sizeof(char) * 512, SYS_PROT_READ | SYS_PROT_WRITE), 512);
                pipe_t* blk_pipe = sys_make_pipe("/pipe/ffs_2/pipe$tmp", strlen("/pipe/ffs_2/pipe$tmp"), buf_pipe, null);

                lba_t* base = sys_alloc_ptr(sizeof(lba_t), SYS_PROT_READ | SYS_PROT_WRITE);
                *base = FFS_2_BASE_LABEL_TABLE;

                blk_pipe->io_ptr = (voidptr_t)base;

                int32_t call_status = sys_dev_ctl(dev, blk_pipe, FFS_2_READ_INDEX);

                memncpy(dlabel, buf_pipe->buf, sizeof(struct ffs_2_disklabel));

                sys_free_ptr(base);

                sys_free_buffer(buf_pipe);
                sys_free_pipe(blk_pipe);

                dev->state = DEV_STATUS_IDLE;

                if (call_status == 0)
                {
                    g_device_found = true;
                    return true;
                }
            }
        }
    }

    return false;
}

bool ffs_2_init_filesystem(void)
{
    struct ffs_2_disklabel label_system;
    zero_memory(&label_system, sizeof(struct ffs_2_disklabel));

    ffs_2_disklabel_init(&label_system);

    if (label_system.d_magic == DLABEL_MAG)
    {
        /* @brief buffer overrun prevention code, add a after end of string. */
        char name[17];

        for (size_t name_len = 0; name_len < 16; name_len++)
        {
            name[name_len] = label_system.d_typename[name_len];
        }

        name[16] = 0;

        sys_print_format("[ffs_2] drive %s is a disklabel.", name);

        return true;
    }

    sys_print_format("[ffs_2] no disk has been fetched.\r\n");

    return false;
}
