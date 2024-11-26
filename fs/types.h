/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <sys/sys.h>
#include <sys/attr.h>

/* i-node for ffs_2 filesystem. */

/* some important types. */
typedef int64_t daddr_t; /* disk address type */
typedef daddr_t lba_t;
typedef uint32_t acl_t;

#define INODE_NAME_LEN (256U)
