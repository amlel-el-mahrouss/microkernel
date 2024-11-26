/*
 *	========================================================
 *
 *	MP MicroKernel
 *
 * 	Date Added: 04/09/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _NFS_H
#define _NFS_H

#include <sys/stdio.h>
#include <nfs/nfs_proto.h>

/* don't bother including pfs.h */
/* just predefine this */

struct pfs_mount_info;

struct pfs_mount_info* nfs_mount(fd_t theFd);
void nfs_unmount(struct pfs_mount_info* mountInfo);

fd_t nfs_open(const char* path, const char* rest);
void nfs_close(fd_t theFd);

fd_t nfs_mkdir(const char* path, const char* rest);
void nfs_rmdir(fd_t theFd);

void nfs_write(fd_t, const char*, size_t, size_t);
void nfs_read(fd_t, char*, size_t, size_t);

#endif /* ifndef _NFS_H */
