/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/info.h>
#include <sys/sys.h>
#include <string.h>
#include <errno.h>
#include <cpu.h>

int sys_get_info(struct sys_diag_info* name)
{
    if (name != null)
    {
        memncpy(name->machine, __arch__, strlen(__arch__));
        memncpy(name->nodename, __unknown__, strlen(__unknown__));
        memncpy(name->sysname, __uname__, strlen(__uname__));
        memncpy(name->version, __unknown__, strlen(__unknown__));
        memncpy(name->release, __release__, strlen(__release__));

        return 0;
    }

    errno = EARG;
    return -1;
}
