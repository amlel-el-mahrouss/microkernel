/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 09/01/2023
 *	Date Edit: 22/01/2023
 *
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <sys/sys.h>

typedef size_t shash_t;

struct strctl
{
	voidptr_t s_data;
	shash_t   s_hash;

	struct strctl* s_prev;
	struct strctl* s_next;
};

size_t sys_strctl_get_size(void);
voidptr_t sys_strctl_get_ptr(const char* hash);

int32_t sys_strctl_add(voidptr_t data, const char* hash);
