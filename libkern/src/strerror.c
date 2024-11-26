/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <strerror.h>
#include <errno.h>
#include <sys/sys.h>

/* last rev 23/12/23 */

static struct error
{
    int	err;
    const char *msg;
} g_error_table[] = {
    {0,		    "operation terminated with success."},
    /* standard errors list */
    {EPERM,		"operation not permitted"},
    {ENOENT,	"no such file or directory"},
    {EIO,		"input/output error"},
    {ENXIO,		"device not configured"},
    {ENOEXEC,	"exec format error"},
    {EBADF,		"bad file descriptor"},
    {ENOMEM,	"cannot allocate memory"},
    {ENODEV,	"operation not supported by device"},
    {ENOTDIR,	"not a directory"},
    {EISDIR,	"is a directory"},
    {EINVAL,	"invalid argument"},
    {EMFILE,	"too many open files"},
    {EFBIG,		"file too large"},
    {EROFS,		"read-only filesystem"},
    {EOPNOTSUPP,"operation not supported"},
    {ETIMEDOUT,	"operation timed out"},
    {ESTALE,	"stale NFS file handle"},
    {EBADRPC,	"RPC struct is bad"},
    {EFTYPE,	"inappropriate file type or format"},
    {EARCH,	    "arch error"},
	{E2SMALL,   "buffer too small"},
	{EDHW,      "hard-drive failure"},
	{ESMP,	    "smp error"},
    {EFAT,	    "fat exec error"},
};

const char* strerror(int err)
{
    int i;

    for (i = 0; g_error_table[i].msg != null; i++)
    {
        if (g_error_table[i].err == err)
            return (g_error_table[i].msg);
    }

    return ("?");
}
