//
//	========================================================
//
//	    MP MicroKernel
// 	    Copyright Amlal EL Mahrouss, all rights reserved.
//
// ========================================================
//

#ifndef _STDLIB_H
#define _STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

void* malloc(unsigned long sz);
void setmalloctag(void* ptr, unsigned long tag);

void* realloc(void* where, unsigned long sz);
void setrealloctag(void* ptr, unsigned long tag);

void* calloc(unsigned long count, unsigned long sz);
void setcalloctag(void* ptr, unsigned long tag);

void free(void*);

#ifdef __cplusplus
};
#endif

#endif // !_STDLIB_H
