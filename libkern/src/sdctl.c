/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/sdctl.h>

////////////////////////////////////////////////////////////////////////////////

// @brief system descriptors

////////////////////////////////////////////////////////////////////////////////

// -------------------------------------------------------------------------
// function: sdctl
// purpose: Tells if these components are at the same level of permissions.
// -------------------------------------------------------------------------

bool sys_sdctl(struct sys_sdctl* lhs, struct sys_sdctl* rhs)
{
    if (lhs == null) return false;
    if (rhs == null) return false;

    return lhs->access == rhs->access;
}

// --------------------------------------------------------------------------------------
// function: sys_sdctl_type
// purpose: Tells the type of software descriptor, what kind of object it is attached on.
// --------------------------------------------------------------------------------------

const char* sys_sdctl_type(struct sys_sdctl* desc)
{
    if (desc != null)
    {
        switch (desc->type)
        {
            case SD_TYPE_PIPE:
                return ("(pipe)");
            case SD_TYPE_DEVICE:
                return ("(device)");
            case SD_TYPE_FILE:
                return ("(file)");
            case SD_TYPE_PROC:
                return ("(process)");
            default:
                return ("(?)");
        }
    }

    return ("(null)");
}
