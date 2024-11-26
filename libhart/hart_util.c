/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <libhart/hart_util.h>
#include <sys/format.h>

// identifies an hart, stupid function
const char* hart_ident(hart_t* hart)
{
	if (hart == null)
		return("(null)");

	char* out_fmt = sys_alloc_ptr(sizeof(char) * 32, SYS_PROT_READ | SYS_PROT_WRITE);
	sys_fmt_string(out_fmt, 32, "hart#%i", *hart);

	return out_fmt;
}
