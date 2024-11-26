/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _SYS_SCHED_CORE_H
#define _SYS_SCHED_CORE_H

#include <hw/cpu.h>
#include <string.h>
#include <sys/user.h>
#include <sys/malloc.h>

#define SCHED_NAME_LEN       (1024)
#define SCHED_PID_MAX        (10000)
#define SCHED_STACK_SIZE     (8192)
#define SCHED_POOL_SIZE      (8192)

#ifdef __SYS_RISCV__

struct sched_snapshot
{
    reg_t ra;
    reg_t sp;
    reg_t s0;
    reg_t s1;
    reg_t s2;
    reg_t s3;
    reg_t s4;
    reg_t s5;
    reg_t s6;
    reg_t s7;
    reg_t s8;
    reg_t s9;
    reg_t s10;
    reg_t s11;
    reg_t satp;
    reg_t mstatus;
    reg_t mepc;
};

#elif defined(__SYS_AMD64__)

struct sched_snapshot
{
    reg_t rbp;
    reg_t rsp;
    reg_t rsi;
    reg_t rdi;
    reg_t rax;
    reg_t rcx;
    reg_t rdx;
    reg_t rflags;
    reg_t r8;
    reg_t r9;
    reg_t r10;
    reg_t r11;
    reg_t r12;
    reg_t r13;
    reg_t r14;
    reg_t r15;
};

#endif

typedef enum
{
    SCHED_TYPE_EXECUTABLE,
    SCHED_TYPE_DAEMON,
    SCHED_TYPE_FORK,
    SCHED_TYPE_INVALID = 0xFF,
    SCHED_TYPE_COUNT,
} SCHED_TYPE;

typedef enum
{
    SCHED_STATUS_ZOMBIE, // task is half dead, half alive
    SCHED_STATUS_LIVING, // task is living his life
    SCHED_STATUS_STARTING, // task is starting
    SCHED_STATUS_STOPPED, // whenever we arrive here, kill the task
    SCHED_STATUS_COUNT,
} SCHED_STATE;

typedef enum
{
    SCHED_FAULT_SEG_FAULT, /* Page fault, task is misbehaving. */
    SCHED_FAULT_CPU_FAULT, /* CPU fault, task is misbehaving. */
    SCHED_FAULT_CORRUPTION, /* Heap corruption, task is misbehaving. */
    SCHED_FAULT_BAD_ARGS, /* Bad arguments, 'exec error' */
    SCHED_FAULT_NON_EXISTENT, /* internal error */
    SCHED_FAULT_COUNT,
} SCHED_FAULT;

typedef enum
{
    SCHED_AFFINITY_HIGH = 3500,
    SCHED_AFFINITY_MEDIUM = 5000,
    SCHED_AFFINITY_LOW = 1000,
} SCHED_AFFINITY;

typedef int64_t pid_t;

typedef int(*sched_main_t)(int argc, char** argv, char** envp, int envp_count);

#endif // !_SYS_SCHED_CORE_H
