/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <ffs_2/inode.h>
#include <sys/malloc.h>

ffs_2_inode_t* ffs_2_create_inode(const char_t* name, size_t used_len)
{
    ffs_2_inode_t* node = sys_alloc_ptr(sizeof(ffs_2_inode_t), SYS_PROT_READ | SYS_PROT_WRITE);

    if (node != nil)
    {
        memset(node, 0, sizeof(ffs_2_inode_t));

        memncpy(node->i_name, name, used_len);
        node->i_name[used_len] = 0;

        return node;
    }

    return nil;
}
