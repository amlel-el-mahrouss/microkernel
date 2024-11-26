/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <cookie/cookie.h>

__COPYRIGHT("$kernel$");

/// \brief buffer overflow protection
/// https://en.wikipedia.org/wiki/Buffer_overflow_protection

// is in page zero by the way.
int32_t __process_cookie_magic;
interface_type __process_interface;

void __init_cookie(void)
{
    __process_cookie_magic = COOKIE_MAGIC;
    __process_interface = 0;

    mach_install_cookie();
}
