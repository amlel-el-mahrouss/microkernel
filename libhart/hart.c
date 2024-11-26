/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <libhart/hart.h>

hart_t* __hart = null;

void __sys_set_hart(hart_t* hart)
{
	if (__hart == null)
		__hart = hart;
}

void __sys_clean_hart(bool do_free)
{
	if (__hart != null) {
		if (do_free)
		{
			sys_free_ptr(__hart);
			__hart = null;
		}
	}
}

bool __sys_hart_should_run(hart_t id)
{
	return __hart && *__hart == id;
}
