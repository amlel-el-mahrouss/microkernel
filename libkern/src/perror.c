/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 04/10/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <strerror.h>
#include <perror.h>
#include <stdio.h>
#include <errno.h>

////////////////////////////////////////////////////////////////////////////////

// @brief print error to stdout.

////////////////////////////////////////////////////////////////////////////////

void sys_print_error(const char* prefix)
{
    sys_print_format("%s: %s\n", prefix, strerror(errno));
}
