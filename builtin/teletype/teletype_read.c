/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <teletype/teletype.h>

int ttyv_read_out(ttyv_t* ttyv, char* out, size_t sz)
{
	if (sz == 0) return 0;

	if (ttyv && out)
	{
		return sys_read(ttyv->out, out, SEEK_SET, sz);
	}

	return -1;
}

int ttyv_read_in(ttyv_t* ttyv, char* out, size_t sz)
{
	if (sz == 0) return 0;

	if (ttyv && out)
	{
		return sys_read(ttyv->in, out, SEEK_SET, sz);
	}

	return -1;
}

int ttyv_read_err(ttyv_t* ttyv, char* out, size_t sz)
{
	if (sz == 0) return 0;

	if (ttyv && out)
	{
		return sys_read(ttyv->err, out, SEEK_SET, sz);
	}

	return -1;
}
