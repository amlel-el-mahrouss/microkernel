/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <procfs/procfs.h>
#include <sys/timer.h>
#include <sys/info.h>
#include <sys/cstr.h>
#include <sys/format.h>
#include <sys/dir.h>
#include <hw/trap.h>
#include <string.h>
#include <sys/fd.h>
#include <kernel.h>
#include <sys/ext.h>
#include <sys/dev.h>
#include <launchdevil.h>

#include <ffs_2/disklabel.h>
#include <virt_disk/virt_disk.h> /* Virtual Disk */

__COPYRIGHT("$kernel$");

#define try_init_feature(EXPR, ERR)\
    if (!(EXPR))\
    {\
        sys_print_format(ERR);\
    }



extern bool g_reboot_requested;
extern int64_t __sys_hart_present;

// needed variables for "system" user.
const gid_t g_kgid                      = 0UL;
uid_t       g_kuid                      = 0UL;

static struct sys_process* g_launchd    = null;

extern uint8_t kext_init_kernel_extensions(void);
extern uint8_t kext_fini_kernel_extensions(void);

int sys_init_kernel(void)
{
#ifdef __KSIMP__
    while (__sys_hart_present < 0) {}
#endif

    if (!sys_heap_ctl(HEAP_STAT_INIT, null, null))
    {
        try_init_feature(sys_heap_ctl(HEAP_STAT_ENABLE, null, null), "[heap] failed to initialize, halting.\r\n");
    }

    try_init_feature(sys_init_device_system(), "[dev] failed to initialize, halting.\r\n");

    sys_init_root_extension("ext-core", kext_init_kernel_extensions, kext_fini_kernel_extensions);

    sys_load_ext();

    if (g_reboot_requested)
        g_reboot_requested = false;

    try_init_feature(sys_init_sched(), "[scheduler] failed to initialize, halting.\r\n");

    g_kuid = sys_add_user("system", g_kgid);

    g_launchd = sys_alloc_ptr(sizeof(struct sys_process), SYS_PROT_READ | SYS_PROT_WRITE);

    sys_sched_create_process(g_launchdevil.name, SCHED_TYPE_EXECUTABLE, g_kuid, g_kgid, g_launchd);
    sys_sched_prepare_process(g_launchd, launchdevil_main);

    sys_set_user(g_kuid);

    sys_sched_set_root_process(g_launchd);

    sys_sched_start_run();

    sys_request_poweroff();

    return 0;
}
