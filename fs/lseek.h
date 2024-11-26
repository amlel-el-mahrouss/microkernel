/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _FS_LSEEK
#define _FS_LSEEK

#include <pfs.h>

lba_t lseek(lba_t source, lba_t reach, lba_t amount);

#endif /* ifndef _FS_LSEEK */
