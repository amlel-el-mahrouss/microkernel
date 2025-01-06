/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _SYS_LOG_H
#define _SYS_LOG_H

#include <escape_codes.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

size_t sys_print_format(char* fmt, ...);
void sys_print_str(char* label);
void sys_print_int(int64_t i);
void sys_print_hex(size_t h);
void sys_print_float(float x);

void init_io(void);

#define sys_print_log(FMT, ...) { sys_print_format("%s[ LOG ] %s", GRN, RESET); sys_print_format(FMT "\r\n", __VA_ARGS__); }

#ifdef __KDEBUG__

#define InitIO() init_io()
#define IOLog(LABEL) sys_print_format("%s[ DEBUG ] %s%s\r\n", GRN, RESET, LABEL)
#define IOLogFormat(FMT, ...) { sys_print_format("%s[ DEBUG ] %s", GRN, RESET); sys_print_format(FMT "\r\n", __VA_ARGS__); }

#define IOLogInfo(LABEL) sys_print_format("%s%s %s%s\r\n", YEL, "[ INFO ]", RESET, LABEL)
#define IOLogError(LABEL) sys_print_format("%s%s %s%s\r\n", BRED, "[ ERROR ]", RESET, LABEL)
#define IOLogCritical(LABEL) sys_print_format("%s%s %s%s\r\n", RED, "[ CRITICAL ]", RESET, LABEL)

#else

#define InitIO()
#define IOLog(LABEL)
#define IOLogFormat(FMT, ...)

#define IOLogInfo(LABEL)
#define IOLogError(LABEL)
#define IOLogCritical(LABEL)

#endif

#endif /* ifndef _SYS_LOG_H */
