#ifndef ASM_H
#define ASM_H

#include <stdint.h>

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t value);
void iowait(void);

#endif

