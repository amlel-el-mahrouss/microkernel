/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <stdint.h>

uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);

void outw(uint16_t port, uint16_t byte);
void outb(uint16_t port, uint8_t byte);
void outl(uint16_t port, uint32_t byte);
