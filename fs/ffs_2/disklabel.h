/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _FFS_DISKLABEL_H
#define _FFS_DISKLABEL_H

/* ffs_2 disklabel implementation */

#include <fs/types.h>
#include <stdbool.h>

#define _PATH_DISKTAB "/etc/disktab"
#define DISKTAB       _PATH_DISKTAB

#define MAX_MAX_PARTS   22

#define DLABEL_MAG      0xfaceface

#define FFS_2_NAME_LEN 16

typedef struct ffs_2_disklabel
{
    uint32_t d_magic;
    uint16_t d_type;
    uint16_t d_subtype;

    char     d_typename[FFS_2_NAME_LEN];
    char     d_packname[FFS_2_NAME_LEN];

    uint64_t d_secsize;
    uint64_t d_nsectors;
    uint64_t d_ntracks;
    uint64_t d_ncynlinders;
    uint32_t d_secpercyl;		/* # of data sectors per cylinder */
	uint32_t d_secperunit;		/* # of data sectors (low part) */

	uint8_t	 d_uid[FFS_2_NAME_LEN];		    /* Unique label identifier. */

    uint8_t  d_lbaext;          /* LBA extended? */

    uint64_t d_startlba;
    uint64_t d_endlba;
    uint64_t d_sectorsz;
} ffs2_disklabel_t;

/* reserved partitions. */

/* floppy disk is just the first 2 drive ports. */

/* Anything that has a system in it. */
#define FFS_LABEL_SYSTEM_DRIVE "/system_drv/"

/* drivers drive */
#define FFS_LABEL_DRIVER_DRIVE "/drivers_drv/"

/* other systems */
#define FFS_LABLEL_OTHER_DRIVE "/other_drv/"

/* no label */
#define FFS_LABEL_NONE         "/no_label_drv/"

/* mass storage partition, no boot, no system. */
#define FFS_LABEL_STANDARD     "/data/"

/* dummy unique id */
#define FFS_INVALID_ID        "FFFF-FFFF-FFFF"
#define FFS_ID_LENGTH         15

char* ffs_2_generate_id(char* real_output_id, size_t len);
bool ffs_2_init_filesystem(void);
bool ffs_2_init_format(int32_t type, int32_t subtype,
                      const char* name,
                      size_t len, size_t sector_len);

enum
{
    FFS_2_SYSTEM_PARTITION = 0xCF, /* partition contains MP MicroKernel. */
    FFS_2_DRIVER_PARTITION = 0xFC, /* partition contains drivers. */
    FFS_2_OTHER_PARTITION  = 0xF9, /* other_sys partition */
    FFS_2_NO_LABEL         = 0x7F, /* no label partition */
    FFS_2_INVALID          = 0xFF, /* mass storage partition. */
};

/* standard i/o device layout. */
#define FFS_2_WRITE_INDEX 1
#define FFS_2_READ_INDEX  0

struct sys_ffs_device_tree
{
    char dev_name[10];
    int  dev_len;
};

#define FFS_DEV_TREE_LEN 7

extern struct sys_ffs_device_tree g_device_tree[];

#endif /* ifndef _FFS_DISKLABEL_H */
