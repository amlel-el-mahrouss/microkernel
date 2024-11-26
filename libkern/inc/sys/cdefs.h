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

#include <stddef.h>
#include <stdint.h>

#ifdef __mpux__
#   undef __mpux__
#endif // ifdef __mpux__

#define __mpux__ __unix__
