/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <sys/sys.h>

#define COOKIE_MAGIC 0xFEEDFACE

__BEGIN_DECLS

int mach_install_cookie(void);

__END_DECLS
