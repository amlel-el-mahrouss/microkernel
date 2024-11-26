/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __PARTITION_MAP_H__
#define __PARTITION_MAP_H__

/* the first 512 > x > 1024 bytes of a disk contains this headers. */

#define UUID_LEN 37

struct boot_block
{
	char magic[4];
    char name[32];
    char uuid[UUID_LEN];
    int version;
    long long int num_blocks;
    long long int sector_sz;
    long long int sector_start;

};

struct part_block
{
    char name[32];
    int magic;
    long long int sector_end;
    long long int sector_sz;
    long long int sector_start;
    short type;
    int version;
    char fs[16]; /* ffs_2 */

};

#define EPM_NAME_PART_SYS "kernsys"

typedef struct part_block part_block_t;
typedef struct boot_block boot_block_t;

#define EPM_MAGIC_X86  "KPMAM"
#define EPM_MAGIC_RV   "KPMRV"

#define EPM_MAX_BLKS   128

#define EPM_BOOT_BLK_SZ sizeof(struct boot_block)
#define EPM_PART_BLK_SZ sizeof(struct part_block)

enum
{
    EPM_AKERNEL = 0xcf,
    EPM_SOLARIS = 0x8f,
    EPM_BSD = 0x9f,
    EPM_LINUX = 0xaf,
};

#endif // ifndef __PARTITION_MAP_H__
