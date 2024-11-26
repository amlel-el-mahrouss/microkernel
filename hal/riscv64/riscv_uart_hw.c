/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <launchdevil.h>
#include <hw/mmap.h>

/* this file handles kernel shell interactions on the U.A.R.T */

static uint8_t* g_uart_ptr = (uint8_t*)0x10000000;

utf32_char_t uart_get_char(void)
{
    uintptr_t ptr = 0x10000000;
    while (!(*(((volatile uint8_t*)ptr) + 0x05) & 0x01));

    return (utf32_char_t)*g_uart_ptr;
}

// we need that one, to avoid sending mutliple chars to UART.
static bool g_locked_put_char = false;

void uart_put_char(utf32_char_t ch)
{
    while (g_locked_put_char);
    g_locked_put_char = true;

    *g_uart_ptr = ch;
    g_locked_put_char = false;
}
