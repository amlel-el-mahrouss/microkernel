/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/utils.h>

struct sched_snapshot* make_sched_snapshot(reg_t ra, reg_t sp)
{
	struct sched_snapshot* snap = sys_alloc_ptr(sizeof(struct sched_snapshot),
    SYS_PROT_READ | SYS_PROT_WRITE | SYS_PROT_EXEC);

	if (!snap) return null;

#ifdef __SYS_RISCV__
	snap->ra = ra;
	snap->sp = sp;
#elif defined(__SYS_AMD64__)
    snap->rax = ra;
    snap->rsp = sp;
#endif

	return snap;
}

int32_t sys_is_alnum(int32_t c)
{
    return (c > 'A' && c <= 'Z') ||
           (c > 'a' && c <= 'z') ||
           (c > '0' && c <= '9');
}

int32_t sys_is_ctrl(int32_t c)
{
    return c < 32 || c == 127;
}
