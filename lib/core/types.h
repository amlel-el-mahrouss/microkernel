/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <errno.h>

/* @brief interface id (can be a class, object, process, daemon). */
typedef uintptr_t interface_type;

int32_t interface_set_field(interface_type interface, const char* key, uintptr_t value);
bool interface_valid(interface_type interface);

#ifndef __MPUX_RUNTIME__
#   define __MPUX_RUNTIME__ 1
#endif /* ifndef __MPUX_RUNTIME__ */
