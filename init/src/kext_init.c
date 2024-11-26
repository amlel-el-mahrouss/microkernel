/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

/* @brief kernel extensions loader. */

#include <nvm_express/nvm_express.h>
#include <ffs_2/disklabel.h>

extern bool g_reboot_requested;

/// load kernel extensions 'ext-core'
/// \return true if successful.
bool kext_init_kernel_extensions(void)
{
    hw_nvme_init();

    if (!g_reboot_requested)
        ffs_2_init_filesystem();

    return true;
}

/// terminates kernel extensions.
/// \return always true, unimplemented.
bool kext_fini_kernel_extensions(void)
{
    return true;
}
