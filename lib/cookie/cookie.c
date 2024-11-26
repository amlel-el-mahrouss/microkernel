/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <cookie/cookie.h>
#include <core/types.h>

__COPYRIGHT("$kernel$");

extern int32_t interface_set_field(interface_type interface, const char* key, uintptr_t value);
extern interface_type __process_interface;

int mach_install_cookie(void)
{
    interface_set_field(__process_interface, "installCookie", true);
}
