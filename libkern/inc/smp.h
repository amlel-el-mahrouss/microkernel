/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

// @brief this file handles symetric multi processing.
// @file smp.h

#include <libhart/hart_ipi.h>
#include <sched/sched.h>
#include <hw/trap.h>
#include <hw/cpu.h>

typedef uint32_t sys_cpuid_t;

struct sys_cpu_desc
{
    char name[32];
    sys_cpuid_t cpu_id;
    bool machine_mode;
    bool used;
    struct sched_snapshot hart_snap;
    struct sched_snapshot process_snap;
};

int mach_start_sched_smp(void);
void mach_stop_sched_smp(void);
bool mach_is_smp_enabled(void);
void mach_ctl(int hart, int flag, ...);

#define M_USER_MODE 0
#define M_USE       1

/* for inter-hart communication */
void mach_smp_sched_hart_recv(struct hart_msg* msg);

/// @brief control mach thread.
/// @param hart the hardware thread.
/// @param flag flag to look for.
/// @param ... varargs.
void mach_ctl(int hart, int flag, ...);
