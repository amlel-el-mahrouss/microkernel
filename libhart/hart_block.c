/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <libhart/hart_block.h>

int __sys_hart_wait(hart_t* hart)
{
	while(hart && __sys_hart_should_run(*hart)) {} // simply hang.
	return (hart != null) ? 0 : -1; // -1 = invalid state.
}
