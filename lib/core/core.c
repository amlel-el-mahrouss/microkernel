/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <core/types.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <string.h>

__COPYRIGHT("$kernel$");

#define MAX_INTERFACES 1024

static struct mpux_interface
{
    char key[64];
    uintptr_t value;
    interface_type interface;
} g_interface_list[MAX_INTERFACES];

static size_t                 g_interface_count = 0UL;
static struct mpux_interface* g_last_interface = NULL;

/// Set a field or creates one.
/// \param interface The mach interface index
/// \param key the key to look for and set.
/// \param value can be anything.
/// \return lookup status.
int32_t interface_set_field(interface_type interface, const char* key, uintptr_t value)
{
    size_t i = 0;
    for (; i < g_interface_count; ++i)
    {
        /* parity check. */
        if (strcmp(key, g_interface_list[i], g_interface_list[i].key) == 0)
        {
            /* interface does not match. */
            if (g_interface_list[i].interface != interface)
                continue;

            g_interface_list[i].value = value;

            goto lookup_done;
        }
        else if (*g_interface_list[i].key == 0)
        {
            if (g_interface_count > MAX_INTERFACES)
            {
                errno = E2BIG;
                return -1;
            }

            strcpy(g_interface_list[i].key, key);

            g_interface_list[i].value = value;
            g_interface_list[i].interface = interface;

            goto lookup_done;
        }
    }

    return -1;

lookup_done:
    ++g_interface_count;
    g_last_interface = &g_interface_list[i];

    return 0;
}

/// is interface valid.
/// \param interface
/// \return
bool interface_valid(interface_type interface)
{
    if (interface == -1)
        return false;

    for (int i = 0; i < g_interface_count; ++i)
    {
        if (g_interface_list[i].interface == interface)
            return true;
    }

    return false;
}
