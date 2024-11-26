/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <core/semaphore.h>
#include <core/types.h>

__COPYRIGHT("$kernel$");

int semaphore_init(semaphore_t *sem, int pshared, unsigned int value)
{
    if (sem == null ||
        !interface_valid(sem->_m_interface))
    {
        errno = EACCES;
        return -1;
    }

    interface_set_field(sem->_m_interface, "isShared", true);
    interface_set_field(sem->_m_interface, "value", value);

    return 0;
}

int semaphore_destroy(semaphore_t *sem)
{
    if (sem == null ||
        !interface_valid(sem->_m_interface))
    {
        errno = EACCES;
        return -1;
    }

    interface_set_field(sem->_m_interface, "isShared", false);
    interface_set_field(sem->_m_interface, "value", 0);

    return 0;
}

int semaphore_wait(semaphore_t *sem)
{
    return interface_set_field(sem->_m_interface, "wait", true);
}

int semaphore_post(semaphore_t *sem)
{
    return interface_set_field(sem->_m_interface, "post", true);
}
