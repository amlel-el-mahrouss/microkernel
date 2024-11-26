/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __SYS_UART_H__
#define __SYS_UART_H__

// UART library

#define SYS_UART_LEN (32U)

#include <sys/sys.h>

/// puts a string inside the UART to TX.
/// \param message
/// \return amount of bytes sent.
int  sys_putstr(const char* message);

/// sends a character into the UART.
/// \param chr the character.
void sys_putc(char chr);

#endif // !__SYS_UART_H__
