/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/sys.h>
#include <hw/uart.h>

// @brief ARC based UART.

#define REG_LSR (0xb0400b14)
#define REG_THR (0xb0400b00)
#define BIT_FULL (0x20)

void sys_putc(char chr)
{
	volatile int* lsr = (volatile int*)REG_LSR; /* Line status register. */
	volatile int* thr = (volatile int*)REG_THR; /* Transmitter holding register. */

	while(((*lsr) & BIT_FULL) == 0); // Wait until THR is empty.

	*thr = chr;
}

int sys_putstr(const char* message)
{
	if (!message) return -1;

    int i = 0;

	while(*message)
	{
        /* the lsr locking is done within putc, we're fine. */
		sys_putc(*message);
		++message;
	}

    return i;
}

#undef REG_LSR
#undef REG_THR
#undef BIT_FULL
