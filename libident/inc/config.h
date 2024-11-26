#ifndef __LIBIDENT_CONF_H__
#define __LIBIDENT_CONF_H__

#ifdef __UXI_TEST__
#   include <stdlib.h>
#   define uxi_alloc malloc
#else
#   include <sys/malloc.h>
#   define uxi_alloc(PTR) sys_alloc_ptr(PTR, SYS_PROT_READ | SYS_PROT_WRITE)
#endif

#endif // __LIBIDENT_CONF_H__
