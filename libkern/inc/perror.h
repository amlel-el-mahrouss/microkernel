/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 04/10/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _PERROR_H
#define _PERROR_H

void sys_print_error(const char* prefix);

#ifdef _POSIX_SOURCE
#define perror sys_print_error
#endif // ifdef _POSIX_SOURCE

#endif /* ifndef _PERROR_H */
