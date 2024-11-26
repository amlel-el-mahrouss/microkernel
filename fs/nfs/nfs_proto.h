/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _NFS_PROTO_H
#define _NFS_PROTO_H

#include <sys/sys.h>

typedef uint32_t attrlist4_t[];
typedef uint32_t bitmap4_t;
typedef uint64_t changeid4_t;
typedef uint64_t clientid4_t;
typedef uint32_t count4_t;
typedef uint64_t length4_t;
typedef uint32_t mode4_t;

typedef uint64_t nfs_cookie4_t;
typedef uint64_t nfs_fh_t;
typedef uint64_t nfs_ftype4_t;

enum nfsstat
{
	NFS_OK = 0,
	NFS_ERR_PERM = 1,
	NFS_ERR_NOENT = 2,
	NFS_ERR_IO = 5,
	NFS_ERR_NXIO = 6,
	NFS_ERR_ACCES = 13,
	NFS_ERR_EXIST = 17,
	NFS_ERR_NODEV = 19,
	NFS_ERR_NOTDIR = 20,
	NFS_ERR_ISDIR = 21,
	NFS_ERR_FBIG = 27,
	NFS_ERR_NOSPC = 28,
	NFS_ERR_ROFS = 30,
	NFS_ERR_NAMETOOLONG = 63,
	NFS_ERR_NOTEMPTY = 66,
	NFS_ERR_DQUOT = 69,
	NFS_ERR_STALE = 70,
	NFS_ERR_WFLUSH = 99,
    NFS_ERR_COUNT,
};

#endif // ifndef _NFS_PROTO_H
