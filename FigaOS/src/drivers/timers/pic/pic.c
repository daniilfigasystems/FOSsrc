#include "timers/pic/pic.h"
#include "io/io.h"

void
PICSendEOI(
    unsigned char irq
)
{
    if (irq >= 8)
        outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}

void PICRemap(
    void
)
{
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
    outb(PIC1 + 1, 4);
    outb(PIC2 + 1, 2);
}

void 
PICUnmask(
    unsigned char irq
) 
{
   if(irq==100) {
      outb(PIC1_DATA,0x00);
      outb(PIC2_DATA,0x00);
   }
   else 
   {
        int irqmask = inb(PIC1_DATA);
        irqmask &= (1<<irq);
        outb(PIC1_DATA,irqmask);

      if(irq < 8)
         outb(PIC1_DATA, irq&0xFF);
      else
         outb(PIC2_DATA, irq>>8);
   }
}