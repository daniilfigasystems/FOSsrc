#include "asm.h"
unsigned char inb(unsigned short port) {
  unsigned char ret;

  __asm__ volatile("in %%dx, %%al" : "=a"(ret) : "Nd"(port));

  return ret;
}

void outb(unsigned short port, unsigned char value) {
  __asm__ volatile("out %%al, %%dx" ::"a"(value), "Nd"(port));
}
void outw(unsigned short port, unsigned char value) {
  __asm__ volatile("out %%ax, %%dx" ::"a"(value), "Nd"(port));
}
unsigned char inw(unsigned short port) {
  unsigned char ret;

  __asm__ volatile("in %%dx, %%ax" : "=a"(ret) : "Nd"(port));

  return ret;
}
void iowait(void) { outb(0x80, 0); }

static inline void cpuid(int code, unsigned int* a, unsigned int* d)
{
    asm volatile ( "cpuid" : "=a"(*a), "=d"(*d) : "0"(code) : "ebx", "ecx" );
}
void getch() {
  asm volatile ( "int $0x16");
}
void cli() {
 asm volatile ("cli");
}
void sti() {
 asm volatile ("sti");
}
void halt() {
  asm volatile ("hlt");
}

void wait_for_io(unsigned int timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}
void suspend(unsigned int timer_count)
{
  wait_for_io(timer_count*0x02FFFFFF);
}
