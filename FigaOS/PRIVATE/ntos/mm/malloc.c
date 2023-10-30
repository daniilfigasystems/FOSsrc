#include "serial.h"
#include "malloc.h"
#include "hal.h"
extern int cr0read();
extern void cr0write();
extern int cr3read();
extern void cr3write();
int kheap = 0x00100000;
#define  mem_min 0x00100001;
#define  mem_max 0x00EFFFFF;
#define  total_mem mem_max - mem_min;

typedef struct {
	unsigned char status;
	unsigned int size;
} alloc_t;
void enable_a20_line() 
{
        write_com(COM1, " setting a20 ");
        inb(0xee);
        cli();
        iowait();
        outb(0x64, 0xAD);
        iowait();
        outb(0x64, 0xD0);
        iowait();
        char a = inb(0x60);
        iowait();
        outb(0x64, 0xD1);
        iowait();
        outb(0x60, a|2);
        iowait();
        outb(0x64, 0xAE);
        sti();

}
 void NMI_enable() 
 {
    outb(0x70, inb(0x70) & 0x7F);
    inb(0x71);
    write_com(COM1, " NMI enabled ");
 }
 
 void NMI_disable() 
 {
    outb(0x70, inb(0x70) | 0x80);
    inb(0x71);
    write_com(COM1, " NMI disabled ");
 }