/*
 *	========================================================
 *
 *	MP MicroKernel - ttyv.h
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <sys/fd.h>
#include <sys/errno.h>

typedef struct ttyv
{
	fd_t out;
	fd_t err;
	fd_t in;
} ttyv_t;

#define TTYV_NEW(PTR, OUT, IN) \
{\
	PTR = sys_alloc_ptr(sizeof(ttyv_t));\
	if (!PTR) errno = EFAULT;\
	PTR->out = sys_open(OUT, "w");\
	PTR->in = sys_open(IN, "r");\
}

int ttyv_write_err(ttyv_t* ttyv, const char* out, size_t sz);
int ttyv_write_out(ttyv_t* ttyv, const char* out, size_t sz);
int ttyv_write_in(ttyv_t* ttyv, const char* out, size_t sz);

int ttyv_read_err(ttyv_t* ttyv, char* out, size_t sz);
int ttyv_read_out(ttyv_t* ttyv, char* out, size_t sz);
int ttyv_read_in(ttyv_t* ttyv, char* out, size_t sz);

int ttyv_redir(fd_t fdin, fd_t fdout, size_t szin, size_t szout);
