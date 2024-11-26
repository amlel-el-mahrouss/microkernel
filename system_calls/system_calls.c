/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <system_calls/system_calls.h>

void sys_dispatch_system_call(sys_snap_t* snapshot)
{
    switch (snapshot->a0)
    {
    case SYS_SYSCTL:
    {
    	do_sysctl((const char*)snapshot->a1, (int)snapshot->a2,  (voidptr_t)snapshot->a3);
    	break;
    }
    case SYS_IOCTL:
    {
    	do_ioctl((int)snapshot->a1, (int)snapshot->a2, (voidptr_t)snapshot->a3);
    	break;
    }
    case SYS_EXECVE:
    {
        do_execve((const char*)snapshot->a1, (char* const*)snapshot->a2, (char* const*)snapshot->a3);
        break;
    }
    case SYS_EXEC:
    {
        do_exec((const char*)snapshot->a1);
        break;
    }
    case SYS_EXIT:
    {
        do_exit((int)snapshot->a1);
        break;
    }
    default:
        break;
    }
}
