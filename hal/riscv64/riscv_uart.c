/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <hw/mmap.h>
#include <hw/uart.h>
#include <string.h>
#include <launchdevil.h>

static struct uart_screen_buffer
{
    char* buffer;
    int x, y;
} g_screen = {
    .buffer = null,
    .x = 25,
    .y = 80,
};

static bool g_locked = false;

void sys_putc(char chr)
{
    uart_put_char(chr);
}

int sys_putstr(const char* msg)
{
    if (msg == null)
        return -1;

    while (g_locked) {}
    g_locked = true;

    /* initialize driver, if not done yet. */
    if (g_screen.buffer == null)
        g_screen.buffer = (char*)sys_get_mmap()[HW_MEMMAP_UART].base_ptr;

    int i = 0;

    for (; i < strlen(msg); i++)
    {
        uart_put_char(msg[i]);
    }

    g_locked = false;

    return i;
}
