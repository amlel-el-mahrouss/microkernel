/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

/*
    the purpose of this file is to provide utilities
    such as identify a hart or stopping one...
 */

#include <libhart/hart.h>
#include <sys/sys.h>
#include <string.h>

// identifies a hart
const char* hart_ident(hart_t* hart);
