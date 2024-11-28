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
#include <sys/format.h>
#include <sys/malloc.h>
#include <sys/dev.h>
#include <string.h>
#include <oseek.h>
#include <lseek.h>
#include <pfs.h>

#include <builtin/uptime/uptime.h>

/**
 * The ffs2 disklabels starts after the xpm blocks.
 * KPM is a partition scheme used by the kernel to know where to boot a system.
 */

#include <fs/partition_map.h>

#define FFS_2_BASE_LABEL_TABLE (sizeof(struct boot_block) * MBS_MAX_BLKS)
#define FFS_2_END_OF_BLT       (FFS_2_BASE_LABEL_TABLE + sizeof(struct ffs_2_disklabel) * MAX_MAX_PARTS)

__COPYRIGHT("$kernel$");

/// @brief generate id for ffs
/// @param real_output_id the output id to generate.
/// @param len the length of it (must be FFS_ID_LENGTH)
/// @return
char* ffs_2_generate_id(char* real_output_id, size_t len)
{
    memset(real_output_id, 0, len);

    size_t i = 0;
    for (; i < len; ++i)
    {
        struct _mpux_time uptime = hw_uptime_fetch();

        real_output_id[i] = uptime.epoch_time / (i + 1);
    }

    return real_output_id;
}

/**
 * @brief Inits and formats a disk with ffs2
 *
 * @param type kind of label.
 * @param subtype it's subtype
 * @param name the label name
 * @param len length of name
 * @param sector_len sector size (512, 1024, 2048...)
 * @return true format was successful
 * @return false failed to format disk
 */
bool ffs_2_init_format(int32_t type,
                        int32_t subtype,
                        const char* name,
                        size_t len,
                        size_t sector_len)
{
    if (len > FFS_2_NAME_LEN ||
        name == nil ||
        *name == 0)
        return false;

    struct ffs_2_disklabel dlabel;

    dlabel.d_magic = DLABEL_MAG;

    char id[FFS_ID_LENGTH];
    ffs_2_generate_id(id, FFS_ID_LENGTH);

    memncpy(dlabel.d_uid, id, FFS_ID_LENGTH);

    dlabel.d_startlba = FFS_2_END_OF_BLT;
    dlabel.d_sectorsz = sector_len;
    dlabel.d_type = type;
    dlabel.d_subtype = subtype; /* not an extended disklabel */

    memncpy(dlabel.d_packname, name, len);
    memncpy(dlabel.d_typename, FFS_LABEL_SYSTEM_DRIVE, strlen(FFS_LABEL_SYSTEM_DRIVE));

    for (size_t device_tree_index = 0; device_tree_index < FFS_DEV_TREE_LEN; ++device_tree_index)
    {
        sys_print_format("[ffs_2] trying to format with label %s\r\n", g_device_tree[device_tree_index].dev_name);

        uintptr_t* indexes = sys_dev_find_tree("/dev/");

        for (size_t device_index = 0; device_index < DEV_ARR_LEN; device_index++)
        {
            if (indexes[device_index] == 0)
                break;

            dev_t* dev = (dev_t*)indexes[device_index];

            while (dev->state == DEV_STATUS_BUSY)
            {
                sys_sleep_for(500);
                sys_print_format("[ffs_2] waiting for device to unlock: %s\r\n", dev->name);
            }

            /* if it passes start format the drive. */
            if (strncmp(dev->name, g_device_tree[device_tree_index].dev_name, strlen(dev->name)) == 0)
            {
                dev->state = DEV_STATUS_BUSY;

                sys_print_format("[ffs_2] formatting %s\r\n", dev->name);

                /* allocate buffer and pipe. */

                buf_t* buf_pipe = sys_make_buffer(sys_alloc_ptr(sizeof(char) * 512,
                                                 SYS_PROT_READ | SYS_PROT_WRITE), 512);

                pipe_t* blk_pipe = sys_make_pipe("/pipe/ffs_2/pipe$tmp",
                                            strlen("/pipe/ffs_2/pipe$tmp"), buf_pipe, null);

                memncpy(buf_pipe->buf, &dlabel, sizeof(struct ffs_2_disklabel));

                uintptr_t* base = sys_alloc_ptr(sizeof(lba_t), SYS_PROT_READ | SYS_PROT_WRITE);
                *base = FFS_2_BASE_LABEL_TABLE;

                blk_pipe->io_ptr = (voidptr_t)base;

                sys_dev_ctl(dev, blk_pipe, FFS_2_WRITE_INDEX);

                memncpy(&dlabel, buf_pipe->buf, sizeof(struct ffs_2_disklabel));

                sys_free_ptr(base);

                sys_free_buffer(buf_pipe);
                sys_free_pipe(blk_pipe);

                dev->state = DEV_STATUS_IDLE;

                return true;
            }
        }
    }

    return false;
}
