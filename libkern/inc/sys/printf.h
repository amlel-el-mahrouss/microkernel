/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#ifdef __INCLUDE_TTY_IO
#   include <stdio.h>
#endif /* ifdef __INCLUDE_TTY_IO */

#ifndef __NO_PRINTF
#   define printf(fmt, ...) sys_print_format(fmt, __VA_ARGS__)
#endif /* ifndef __NO_PRINTF */
