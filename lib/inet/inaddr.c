/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <inet/inaddr.h>
#include <string.h>

extern void* malloc(size_t sz);

/* internet protocol implementation for MP MicroKernel */

struct in_addr* inet_addr(const uint8_t* addr)
{
    if (strnlen(addr, 12) > 8)
        return null;

    struct in_addr* inaddr = malloc(sizeof(struct in_addr));

    if (inaddr == null)
        return null;

    for (size_t i = 0; i < strlen(addr); ++i)
    {
        if (addr[i] != '.')
        {
            if (inaddr->s_b1 != 0xFF)
            {
                inaddr->s_b1 = addr[i];
                continue;
            }
            else if (inaddr->s_b2 != 0xFF)
            {
                inaddr->s_b2 = addr[i];
                continue;
            }
            else if (inaddr->s_b3 != 0xFF)
            {
                inaddr->s_b3 = addr[i];
                continue;
            }
            else if (inaddr->s_b4 != 0xFF)
            {
                inaddr->s_b4 = addr[i];
                continue;
            }
        }
    }

    return inaddr;
}
