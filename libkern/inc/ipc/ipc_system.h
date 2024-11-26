/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MPUX_IPC_SYS_H
#define _MPUX_IPC_SYS_H

#include <sched/sched.h>
#include <sys/fd.h>

#define IPC_STAT_OK (0U) /* ok */
#define IPC_STAT_ACK (1U) /* ipc packet has been acknowledged */
#define IPC_STAT_ACCESS (2U) /* access denied */
#define IPC_STAT_STOP (3U) /* ipc descriptor is now free */
#define IPC_STAT_COUNT (4U) /* number of stat variables */

#define IPC_MAX_CONN (100U)

typedef int32_t ipc_id_t; /* ipc identifier. */

struct ipc_addr
{
    pid_t a_source;
    pid_t a_dest;
    ipc_id_t a_id;
    int32_t* a_stat;
    voidptr_t a_contact_buffer;
    size_t a_contact_buffer_sz;
};

#define IPC_ADDR_SZ (sizeof(struct ipc_addr))

struct ipc_context
{
    struct ipc_addr** i_address_list;
    pid_t i_pid;
};

int32_t sys_ipc_switch(struct ipc_context* ctx);

int32_t sys_ipc_send(struct ipc_addr* addr_info, int32_t message);
struct ipc_addr* sys_ipc_make_addr(pid_t dst, pid_t src);
ipc_id_t sys_ipc_connect(struct ipc_addr* addr);
int32_t sys_ipc_stat(struct ipc_addr* addr);
void sys_ipc_close(ipc_id_t ipc);

#endif /* ifndef _MPUX_IPC_SYS_H */
