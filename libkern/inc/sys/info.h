/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _UTSNAME_H
#define _UTSNAME_H

struct sys_diag_info
{
    char sysname[65];  //  name of this implementation of the operating system
    char nodename[65]; //  name of this node within an implementation-dependent
                       // communications network
    char release[65];  // current release level of this implementation
    char version[65];  // current version level of this release
    char machine[65];  // name of the hardware type on which the system is running
};

int sys_get_info(struct sys_diag_info *name);

#endif /* ifndef _UTSNAME_H */
