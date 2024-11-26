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
#include <sys/malloc.h>

typedef int64_t hart_t;

void __sys_set_hart(hart_t* hart);
bool __sys_hart_should_run(hart_t id);
void __sys_clean_hart(bool do_free);

extern hart_t* __hart;

#define INVALID_HART (-1)
