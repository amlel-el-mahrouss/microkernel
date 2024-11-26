/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef MSL_SEM_H
#define MSL_SEM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <msl/types.h>

typedef struct __mpux_sem
{
    interface_type _m_interface;
} semaphore_t;

int semaphore_init(semaphore_t *sem, int pshared, unsigned int value);
int semaphore_destroy(semaphore_t *sem);
int semaphore_wait(semaphore_t *sem);
int semaphore_post(semaphore_t *sem);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* ifndef MSL_SEM_H */
