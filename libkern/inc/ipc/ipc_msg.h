/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _SYS_IPC_MSG_H
#define _SYS_IPC_MSG_H

//! this is based on a network architecture.
//! so we can guarantee communication with sockets easy.

#include <sched/sched.h>
#include <sys/pipe.h>
#include <ipc/ipc_system.h>

struct _mach_ipc_msg_body;
struct _mach_ipc_msg_header;

//! @brief mach ipc header

typedef struct _mach_ipc_msg_header
{
    char m_process_name[SCHED_NAME_LEN];
    pid_t m_process_id;
    uint64_t m_contact_port;
    uint64_t m_message_subject;
    struct _mach_ipc_msg_body* m_body;
} ipc_msg_header_t;

//! @brief Reserved for internal uses.
typedef struct _mach_ipc_msg_body
{
    voidptr_t m_data_ptr;
    int32_t m_data_type;
    size_t m_data_size;
} ipc_msg_body_t;


// @brief sets a new request header.
ipc_msg_header_t* mach_new_request(uint64_t port, uint64_t subject);

// @brief sets body for request.
void mach_set_contents(ipc_msg_body_t* bodyptr, ipc_msg_header_t* headerptr);

#endif /* ifndef _SYS_IPC_MSG_H */
