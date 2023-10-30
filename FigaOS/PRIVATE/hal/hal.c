#include "serial.h"
void hal_init()
{
	
}

void send_eoi(unsigned char irq)
{
}

void set_int(int i, unsigned int addr)
{

}

unsigned char inb(unsigned short portid)
{
	unsigned char ret;
	asm volatile("inb %%dx, %%al":"=a"(ret):"d"(portid));
	return ret;
}
unsigned short inw(unsigned short portid)
{
	unsigned short ret;
	asm volatile("inw %%dx, %%ax":"=a"(ret):"d"(portid));
	return ret;
}
unsigned int inl(unsigned short portid)
{
	unsigned int ret;
	asm volatile("inl %%dx, %%eax":"=a"(ret):"d"(portid));
	return ret;
}
void outb(unsigned short portid, unsigned char value)
{
	asm volatile("outb %%al, %%dx": :"d" (portid), "a" (value));
}
void outw(unsigned short portid, unsigned short value)
{
	asm volatile("outw %%ax, %%dx": :"d" (portid), "a" (value));
}
void outl(unsigned short portid, unsigned int value)
{
	asm volatile("outl %%eax, %%dx": :"d" (portid), "a" (value));
}
void iowait(void) { outb(0x80, 0); }