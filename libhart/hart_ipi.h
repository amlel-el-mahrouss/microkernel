/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _LIBHART_IPI_H
#define _LIBHART_IPI_H

#include <sys/sys.h>

/*
 * This file helps send message to a specific core/hart.
 * A hart is a unique and isolated thread. take it as a hardware thread.
 */

enum IPI_MSG_KIND
{
    IPI_MSG_KIND_START, /* start a core */
    IPI_MSG_KING_MEMCPY, /* copy memory to hart */
    IPI_MSG_KIND_STOP, /* stop the current core */
    IPI_MSG_KIND_TASK_AVAIL, /* tell the core that there is free task */
    IPI_MSG_KIND_CHILL, /* Much like IPI_MSG_KIND_STOP but instead of stopping and **freeing** the core is being put in sleep. */
};

#ifndef _LIBHART_MAX
#define _LIBHART_MAX (16U)
#endif /* ifndef _LIBHART_MAX */

#define _LIBHART_INVALID (0xFF)

struct hart_msg;
struct hart_mask;

/*
 * [0] = 0xFF <-- always 0xFF by default; if not, it tells the boot's id.
 * [1] = 0x5 <-- this core has an id of five.
 * [2] = 0xFF
 * ...
 * [15] = 0xF
 *
 * this struct is a handle to all the cores, that the OS has access to.
 */

typedef void(*hart_recv_t)(struct hart_msg* msg);

struct hart_mask
{
    struct
    {
        hart_recv_t recv_channel[4];
        size_t free_channel;
    } descriptor;

    uint8_t cpu[_LIBHART_MAX];
};

void hart_send_ipi(struct hart_mask* restr, size_t cnt, struct hart_msg* msg);

struct hart_msg
{
    uint8_t m_mag;
    enum IPI_MSG_KIND m_msg;
    uint8_t m_from; /* which hart? */
    voidptr_t m_dat; /* the data, in the case of a mem copy command. */
    uint8_t m_to; /* to which hart? */
    size_t m_sz;
};

#endif /* ifndef _LIBHART_IPI_H */
