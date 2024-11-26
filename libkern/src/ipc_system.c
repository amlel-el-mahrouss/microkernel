/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 13/04/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <ipc/ipc_system.h>

#include <sched/sched.h>
#include <sys/malloc.h>
#include <sys/errno.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// @brief This file handles the ipc API for each servers.
// Maintainers: amlel

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__COPYRIGHT("$kernel$");

// last-rev: 11/09/23

struct ipc_context* g_ipc_ctx = null;
ipc_id_t g_ipc_counter = 0UL;

int32_t sys_ipc_switch(struct ipc_context* ctx)
{
    if (ctx != null)
        ctx = g_ipc_ctx;

    return (g_ipc_ctx != ctx);
}

struct ipc_addr* sys_ipc_make_addr(pid_t dst, pid_t src)
{
    if (dst == -1 ||
    	src == -1)
    {
        errno = EARG;
        return null;
    }

    struct ipc_addr* addr = sys_alloc_ptr(IPC_ADDR_SZ, SYS_PROT_READ | SYS_PROT_WRITE);

    addr->a_source = src;
    addr->a_dest = dst;
    addr->a_stat = null;

    errno = 0;
    return addr;
}

ipc_id_t sys_ipc_connect(struct ipc_addr* addr)
{
    struct sys_process* process = sys_get_root_process();

    while (process != null)
    {
        bool found = process->p_thread->t_pid == addr->a_source; /* has the dest pid been found? */

        if (found)
        {
            ipc_id_t id = ++g_ipc_counter;

            if (id == -1)
            {
                errno = ECONNREFUSED;
                return -1;
            }

            errno = 0;

            addr->a_id = id;

            g_ipc_ctx->i_address_list[id - 1] = addr;

            return id;
        }

        process = process->p_next;
    }

    return -1;
}

void sys_ipc_close(ipc_id_t ipc)
{
    struct ipc_addr* addr =  g_ipc_ctx->i_address_list[ipc - 1];

    if (addr->a_id == ipc)
    {
        if (addr->a_stat != null)
            *addr->a_stat = IPC_STAT_STOP;

        g_ipc_ctx->i_address_list[ipc - 1] = null;

        --g_ipc_counter;

        errno = 0;
        return;
    }

    errno = EARG;
}

int32_t sys_ipc_stat(struct ipc_addr* addr)
{
    if (addr != null)
    {
        assert(addr->a_stat != null);
        return *addr->a_stat;
    }

    return -1;
}

#include <ipc/ipc_msg.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @brief IPC listener
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int32_t sys_ipc_listen(struct ipc_addr* addr, struct _mach_ipc_msg_header* hdrptr)
{
    if (addr == null ||
        *addr->a_stat != IPC_STAT_OK)
        return -ENOIPC;

    if (hdrptr != nil &&
        hdrptr->m_body != nil &&
        addr->a_id == hdrptr->m_contact_port &&
        addr->a_contact_buffer_sz == hdrptr->m_body->m_data_size)
    {
        memncpy(addr->a_contact_buffer, hdrptr->m_body->m_data_ptr, hdrptr->m_body->m_data_size);

        return 0;
    }

    return -EACCES;
}
