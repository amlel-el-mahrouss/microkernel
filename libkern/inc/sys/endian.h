/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MP_ENDIAN_H
#define _MP_ENDIAN_H

#include <stdint.h>

/* @brief endianess related functions */
/* mainly used, because internet is using big endian. */

#define endian_is_big(addr, value) (((char*)addr)[0] == value)
#define endian_is_little(addr, value) !endian_is_big(addr, value)

static inline uint16_t sys_switch_endian16(uint16_t nb)
{
    return (nb >> 8) | (nb << 8);
}

static inline uint32_t sys_switch_endian32(uint32_t nb)
{
    return ((nb>>24) & 0xff) | ((nb<<8) & 0xff0000) | ((nb>>8) & 0xff00) | ((nb<<24) & 0xff000000);
}

#endif // ifndef _MP_ENDIAN_H
