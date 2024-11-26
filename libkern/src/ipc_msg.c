/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 11/09/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */


#include <sys/thread_local.h>
#include <ipc/ipc_msg.h>
#include <errno.h>

__COPYRIGHT("$kernel$");

// @brief sets a new request header.
ipc_msg_header_t* mach_new_request(uint64_t port, uint64_t subject)
{
    ipc_msg_header_t* hdr = sys_tls_alloc(sizeof(ipc_msg_header_t));

    if (hdr == nil)
    {
        errno = ENOMEM;
        return nil;
    }

    hdr->m_message_subject = subject;
    hdr->m_contact_port = port;

    return hdr;
}

// @brief sets body for request.
void mach_set_contents(ipc_msg_body_t* bodyptr, ipc_msg_header_t* headerptr)
{
    if (headerptr != nil &&
        bodyptr != nil)
    {
        headerptr->m_body = bodyptr;
        errno = 0;

        return;
    }

    errno = EACCES;
}
