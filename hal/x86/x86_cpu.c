/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/sys.h>
#include <x86_cpu.h>

void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile ("outb %%al, %1"  : : "a" (value), "Nd" (port) : "memory");
}

void outw(uint16_t port, uint16_t value)
{
    __asm__ volatile ("outw %%ax, %1"  : : "a" (value), "Nd" (port) : "memory");
}

void outl(uint16_t port, uint32_t value)
{
    __asm__ volatile ("outl %%eax, %1" : : "a" (value), "Nd" (port) : "memory");
}

uint8_t inb(uint16_t port)
{
    uint8_t value = 0UL;
    __asm__ volatile ("inb %1, %%al"  : "=a" (value) : "Nd" (port) : "memory");

    return value;
}

uint16_t inw(uint16_t port)
{
    uint16_t value = 0UL;
    __asm__ volatile ("inw %1, %%ax"  : "=a" (value) : "Nd" (port) : "memory");

    return value;
}

uint32_t inl(uint16_t port)
{
    uint32_t value = 0UL;
    __asm__ volatile ("inl %1, %%eax" : "=a" (value) : "Nd" (port) : "memory");

    return value;
}
