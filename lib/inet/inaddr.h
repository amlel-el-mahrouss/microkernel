/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __INET_ADDR_H__
#define __INET_ADDR_H__

#include <sys/sys.h>
#include <inet/types.h>

struct in_addr
{
    union
    {
        struct
        {
            u_char s_b1;
            u_char s_b2;
            u_char s_b3;
            u_char s_b4;
        } S_un_b;

#define s_b1 S_un.S_un_b.s_b1
#define s_b2 S_un.S_un_b.s_b2
#define s_b3 S_un.S_un_b.s_b3
#define s_b4 S_un.S_un_b.s_b4

        struct
        {
            u_short s_w1;
            u_short s_w2;
        } S_un_w;

        u_long S_addr;
    } S_un;
};

struct in_addr* inet_addr(const uint8_t* addr);

typedef struct in_addr in_addr_t;

#endif /* ifndef __INET_ADDR_H__ */
