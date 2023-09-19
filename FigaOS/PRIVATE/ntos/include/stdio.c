#include "stdio.h"

unsigned char inb(unsigned short port) {
  unsigned char ret;

  __asm__ volatile("in %%dx, %%al" : "=a"(ret) : "Nd"(port));

  return ret;
}

void outb(uint16_t port, uint8_t value) {
  __asm__ volatile("out %%al, %%dx" ::"a"(value), "Nd"(port));
}

void iowait(void) { outb(0x80, 0); }
