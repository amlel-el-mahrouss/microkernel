/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

// Serial logging facilities.

#include <sys/log.h>
#include <x86_cpu.h>
#include <sys/sys.h>

#define COM1_PORT (0x3F8)

static bool g_enable = false;

void init_io(void)
{
    if (g_enable) return;

    outb (COM1_PORT + 1, 0x00);
    outb (COM1_PORT + 3, 0x80);
    outb (COM1_PORT + 0, 0x03);
    outb (COM1_PORT + 1, 0x00);
    outb (COM1_PORT + 3, 0x02);
    outb (COM1_PORT + 2, 0xC7);
    outb (COM1_PORT + 4, 0x0B);

    g_enable = true;
}

void sys_print_str(char* message)
{
    if (!g_enable) init_io();

    for (size_t index = 0; message[index] != '\0'; ++index)
        outb(COM1_PORT, message[index]);

    outb(COM1_PORT, '\0');
}

#undef COM1_PORT
