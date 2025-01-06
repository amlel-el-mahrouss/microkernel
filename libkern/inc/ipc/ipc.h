/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MP_IPC_H
#define _MP_IPC_H

#include <ipc/ipc_msg.h>
#include <ipc/ipc_system.h>

// last rev 25/11/23

int32_t sys_ipc_listen(struct ipc_addr* addr, struct _mach_ipc_msg_header* hdrptr);

#endif /* ifndef _MP_IPC_H */
