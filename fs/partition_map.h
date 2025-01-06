/*
 *	========================================================
 *
 *	mp-boot
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __PARTITION_MAP_H__
#define __PARTITION_MAP_H__

#include <sys/types.h>

/**
 * 
 * MBS, wrapper over mp's disklabels.
 * 
 */

#define MBS_NAME_LEN 32
#define MBS_MAG_LEN 4
#define MBS_UUID_LEN 37

/* the first 512 > x > 1024 bytes of a disk contains this headers. */

/**
 * @brief The MP Boot Sector bootloader block.
 * 
 */
struct boot_block
{
	char magic[MBS_MAG_LEN];
    char name[MBS_NAME_LEN];
    char uuid[MBS_UUID_LEN];
    int version;
    long long int num_blocks;
    long long int sector_sz;
    long long int sector_start;
    
};

/**
 * @brief The MP Boot Sector partition block.
 * 
 */
struct part_block
{
    char name[MBS_NAME_LEN];
    int magic;
    long long int sector_end;
    long long int sector_sz;
    long long int sector_start;
    short type;
    int version;
    char fs[16]; /* ffs_2 */

};

typedef struct part_block part_block_t;
typedef struct boot_block boot_block_t;

/* @brief AMD64 magic for MP Boot Sector */
#define MBS_MAG   "  MBS"

#define MBS_MAX_BLKS   (128U)

#define MBS_BOOT_BLK_SZ sizeof(struct boot_block)
#define MBS_PART_BLK_SZ sizeof(struct part_block)

//! version types.
//! use in boot block version field.

enum
{
    MBS_MP                = 0xcf,
    MBS_LINUX             = 0x8f,
    MBS_BERKELEY_SOFTWARE = 0x9f,
    MBS_CUSTOM             = 0x1f,
};

#endif // ifndef __PARTITION_MAP_H__
