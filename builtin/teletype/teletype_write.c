/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <teletype/teletype.h>

int ttyv_write_out(ttyv_t* ttyv, const char* out, size_t sz)
{
	if (sz == 0) return 0;

	if (ttyv && out)
	{
		return sys_write(ttyv->out, out, SEEK_SET, sz);
	}

	return -1;
}

int ttyv_write_in(ttyv_t* ttyv, const char* out, size_t sz)
{
	if (sz == 0) return 0;

	if (ttyv && out)
	{
		return sys_write(ttyv->in, out, SEEK_SET, sz);
	}

	return -1;
}

int ttyv_write_err(ttyv_t* ttyv, const char* out, size_t sz)
{
	if (sz == 0) return 0;

	if (ttyv && out)
	{
		return sys_write(ttyv->err, out, SEEK_SET, sz);
	}

	return -1;
}
