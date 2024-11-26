/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _FFS_2_INODE_H
#define _FFS_2_INODE_H

#include <ffs_2/disklabel.h>
#include <fs/types.h>

/// \brief fast filesystem 2 index node
/// this is used to keep track of recorded files.
/// there may be multiple inodes with the same name (for fragmented files)
typedef struct attr(packed) ffs_2_inode
{
    char_t  i_name[INODE_NAME_LEN];
    int32_t i_posix;
    int32_t i_attr;
    daddr_t i_addr;
    size_t  i_size;
    size_t  i_flags;
    daddr_t i_sibling[3];
} ffs_2_inode_t;

#define FFS_2_SEP  '/'

#define FFS_2_UP   ".."
#define FFS_2_ROOT "/"

/// \brief Creates a new empty node
/// \param name The node name
/// \param used_len The used bytes for this node.
/// \return a ffs_2 node.
ffs_2_inode_t* ffs_2_create_inode(const char_t* name, size_t used_len);

/// @brief Usage reference type.
typedef uintptr_t* ffs_2_use_ref_t;

#define FFS2_IS_USED(X)     (*X) > 0
#define FFS2_FREE(X, PTR)   if (*X == 0) { sys_free_ptr(PTR); }

#endif // ifndef _FFS_2_INODE_H
