/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __SYS_CTL_H__
#define __SYS_CTL_H__

#include <sys/sys.h>

struct sysctl;

#define SYSCTL_NAME_LEN (256U)

typedef int (*sysctl_proc_handler_t)(struct sysctl *ctl, int write, voidptr_t buffer,
                                     size_t *lenPtr, off_t *posPtr);

typedef struct sysctl
{
    char_t s_name[SYSCTL_NAME_LEN];
    sysctl_proc_handler_t s_proc_handler;
    voidptr_t s_data;
    int32_t s_mask;
    int32_t s_mode;
} sysctl_t;

typedef sysctl_t* sysctl_ptr_t;

#define sysctl_new_ptr() sys_alloc_ptr(sizeof(struct sysctl), SYS_PROT_READ | SYS_PROT_WRITE)
#define sysctl_delete_ptr(ptr) { if (sizeof(ptr) == sizeof(struct sysctl)) { sys_free_ptr(ptr); } }

#endif // !__SYS_CTL_H__
