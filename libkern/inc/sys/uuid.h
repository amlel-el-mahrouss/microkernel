/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MP_UUID_H
#define _MP_UUID_H

#include <sys/sys.h>

typedef uint16_t uuid_t[16];

#define UUID_BEG_STR '['
#define UUID_END_STR ']'

#define UUID_DEFINE(u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11,u12,u13,u14,u15) {u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11,u12,u13,u14,u15}
#define UUID_NIL() UUID_DEFINE(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)

#define UUID_TYPE_SHIFT (4)
#define UUID_TYPE_MASK  (0xf)

#define UUID_TYPE_DCE_NIL    (0)
#define UUID_TYPE_DCE_TIME   (1)
#define UUID_TYPE_DCE_SECURITY (2)
#define UUID_TYPE_DCE_MD5    (3)
#define UUID_TYPE_DCE_RANDOM (4)
#define UUID_TYPE_DCE_SHA1   (5)

#endif /* ifndef _MP_UUID_H */
