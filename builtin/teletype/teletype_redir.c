/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <teletype/teletype.h>
#include <string.h>

// cat "hello, world" | mail -s lol dest@hotmail.net
int ttyv_redir(fd_t fdin, fd_t fdout, size_t szin, size_t szout)
{
	if (szin == 0) return E2SMALL;
	if (fdin == -1 || fdout == -1) return -1;

	char in[szin];
	memset(in, 0, szin);

	if (!sys_read(fdin, in, SEEK_SET, szin)) return -2; // EFDIN is minus two
	if (!sys_write(fdout, in, SEEK_SET, szout)) return -1; // EFDOUT is minus one

	return 0; // every had gone ok.
}
