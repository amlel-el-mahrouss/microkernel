/*
 *	========================================================
 *
 *  MP MicroKernel
 *  Date Added: 08/01/2023
 *  Last Edit: 27/04/2023
 *  Copyright Amlal EL Mahrouss, all rights reserved.
 *  File: sdctl.h
 *  Purpose: System descriptor for files, pipes or devices.
 *
 * ========================================================
 */

#ifndef _SYS_SDCTL_H
#define _SYS_SDCTL_H

#include <sys/sys.h>

#define SD_TYPE_FILE       (2U)
#define SD_TYPE_DEVICE     (4U)
#define SD_TYPE_PROC       (8U)
#define SD_TYPE_PIPE       (12U)

#define SD_ACCESS_SUPER    (6U)
#define SD_ACCESS_STANDARD (8U)

#define sdctl_has_flag(sd, flag) (sd.access & flag)
#define sdctl_set_flag(sd, flag) (sd.access |= flag)

struct sys_sdctl
{
   uint8_t type; // SD_TYPE_FILE, SD_TYPE_PIPE, SD_TYPE_DEVICE
   uint8_t access; // access type (can only be one!)
   uint32_t perms; // the permission it has.
}; // system descriptor

bool sys_sdctl(struct sys_sdctl* lhs, struct sys_sdctl* rhs);
const char* sys_sdctl_type(struct sys_sdctl* desc);

#endif /* !_SYS_SDCTL_H */
