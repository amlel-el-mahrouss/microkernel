/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <libfdt/libfdt_env.h>
#include <libfdt/libfdt.h>

#include <sys/array.h>

struct fdt_err
{
    const char* e_str;
};

/**
 * @brief Errno like structure to convert errors to string.
 *
 */
#define fdt_error(VAL) \
	[(VAL)] = { .e_str = #VAL, }

static struct fdt_err g_fdtErrTbl[] = {
	fdt_error(FDT_ERR_NOTFOUND),
	fdt_error(FDT_ERR_EXISTS),
	fdt_error(FDT_ERR_NOSPACE),

	fdt_error(FDT_ERR_BADOFFSET),
	fdt_error(FDT_ERR_BADPATH),
	fdt_error(FDT_ERR_BADPHANDLE),
	fdt_error(FDT_ERR_BADSTATE),

	fdt_error(FDT_ERR_TRUNCATED),
	fdt_error(FDT_ERR_BADMAGIC),
	fdt_error(FDT_ERR_BADVERSION),
	fdt_error(FDT_ERR_BADSTRUCTURE),
	fdt_error(FDT_ERR_BADLAYOUT),
	fdt_error(FDT_ERR_INTERNAL),
	fdt_error(FDT_ERR_BADNCELLS),
	fdt_error(FDT_ERR_BADVALUE),
	fdt_error(FDT_ERR_BADOVERLAY),
	fdt_error(FDT_ERR_NOPHANDLES),
	fdt_error(FDT_ERR_BADFLAGS),
	fdt_error(FDT_ERR_ALIGNMENT),
};

#define fdt_error_length() mpux_array_size(g_fdtErrTbl)

const char* fdt_strerror(int32_t errval)
{
    if (errval > 0)
    {
		return ("<valid offset/length>");
	}
    else if (errval == 0)
	{
        return ("<no error>");
	}
    else if (-errval < fdt_error_length())
    {
        const char* serr = g_fdtErrTbl[errval].e_str;

        if (serr != null)
		{
			return serr;
		}
    }

    return ("<unknown error>");
}
