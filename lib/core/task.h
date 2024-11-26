/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __MACH_TASK_H__
#define __MACH_TASK_H__

/* @brief specify threading model method */
#define THREADING_MODEL "mpux"

/* @brief mpux thread handle */
typedef long mtask_t;

/* @brief mpux access control layer. */
typedef long macl_t;

#endif // ifndef __MACH_TASK_H__
