#include <abi/virtual.h>
#include <sched/sched.h>

__COPYRIGHT("$kernel$");

/* last rev 23/12/23 */

/*
 * synname can be pushed by the ABI
 * in order to define an undefined symbol's name */
void __sys_purecall(const char* symname) { }
