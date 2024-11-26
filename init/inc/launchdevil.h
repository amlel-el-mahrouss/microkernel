/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _LAUNCHDEVIL_H
#define _LAUNCHDEVIL_H

#include <sys/sys.h>
#include <sys/fd.h>

typedef char utf8_char_t;
typedef uint16_t utf16_char_t;
typedef uint32_t utf32_char_t;

utf32_char_t uart_get_char(void);
void uart_put_char(utf32_char_t c);

#define LD_MAX_BUF (1024U)
#define LD_MAX_HISTORY_SZ (32U)

struct launchd_term
{
    char name[64];
    size_t cursor_x;
    size_t cursor_y;
    size_t history_cursor;
    char history[LD_MAX_HISTORY_SZ][LD_MAX_BUF];
    char buffer[LD_MAX_BUF];
};

extern struct launchd_term g_launchdevil;

int launchdevil_main(int argc, char** argv, char** envp, int envp_count);

#endif /* ifndef _LAUNCHDEVIL_H */
