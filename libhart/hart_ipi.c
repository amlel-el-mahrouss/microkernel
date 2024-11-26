/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <libhart/hart_ipi.h>
#include <sys/errno.h>

static bool hart_is_channel_free(struct hart_mask* msg)
{
    return msg->descriptor.free_channel != 0xFF;
}

void hart_send_ipi(struct hart_mask* restr, size_t cnt, struct hart_msg* msg)
{
    if (restr == null || msg == null) return;

    for (int i = 0; i < cnt; ++i)
    {
        if (restr->cpu[i] != _LIBHART_INVALID)
        {
            while (!hart_is_channel_free(restr)) {}
            restr->descriptor.recv_channel[restr->descriptor.free_channel](msg);

            break;
        }
    }
}
