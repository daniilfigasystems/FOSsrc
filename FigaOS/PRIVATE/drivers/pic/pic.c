#include "pic.h"
#include "hal.h"
#include "serial.h"
void pic_remap(int offset1, int offset2)
{
    unsigned char a1 = inb(PIC1_DATA);
    unsigned char a2 = inb(PIC2_DATA);
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    iowait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    iowait();
    outb(PIC1_DATA, offset1);
    iowait();
    outb(PIC2_DATA, offset2);
    iowait();
    outb(PIC1_DATA, 4);
    iowait();
    outb(PIC2_DATA, 2);
    iowait();
	outb(PIC1_DATA, ICW4_8086);               
	iowait();
	outb(PIC2_DATA, ICW4_8086);
	iowait();
	outb(PIC1_DATA, a1); 
	outb(PIC2_DATA, a2);
    write_com(COM1, " PIC initialization... ");
    if (PIC1 == 0 & PIC2 == 0)
    write_com(COM1, " initialization PIC failed ");
    else
    write_com(COM1, " initializated PIC! ");   
}
void IRQ_set_mask(unsigned char IRQline) {
    unsigned short port;
    unsigned char value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}
void IRQ_clear_mask(unsigned char IRQline) {
    unsigned short port;
    unsigned char value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}
void PIC_sendEOI(unsigned char irq) {
    if (irq >= 8)
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}