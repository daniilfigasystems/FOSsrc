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
    /*
    outb(PIC2_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);

    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);

    outb(PIC2_DATA, 0x20);
    outb(PIC2_DATA, 0x28);

    outb(PIC2_DATA, 4);
    outb(PIC2_DATA, 2);

    outb(0xa0, 0x01);
    outb(0xa0, 0x01);

    asm volatile("sti");
    outb(PIC2_DATA, 0x00);
    outb(PIC2_DATA, 0x00);
    */
     /* Mask all interrupts on both PICs. */
    outb (PIC1_DATA, 0xff);
    outb (PIC2_DATA, 0xff);

    /* Initialize master. */
    outb (0x20, 0x11); /* ICW1: single mode, edge triggered, expect ICW4. */
    outb (PIC1_DATA, 0x20); /* ICW2: line IR0...7 -> irq 0x20...0x27. */
    outb (PIC1_DATA, 0x04); /* ICW3: slave PIC on line IR2. */
    outb (PIC1_DATA, 0x01); /* ICW4: 8086 mode, normal EOI, non-buffered. */

    /* Initialize slave. */
    outb (0xa0, 0x11); /* ICW1: single mode, edge triggered, expect ICW4. */
    outb (PIC2_DATA, 0x28); /* ICW2: line IR0...7 -> irq 0x28...0x2f. */
    outb (PIC2_DATA, 0x02); /* ICW3: slave ID is 2. */
    outb (PIC2_DATA, 0x01); /* ICW4: 8086 mode, normal EOI, non-buffered. */

    outb(0x70, inb(0x70) & 0x7F);
    inb(0x71);

    /* Unmask all interrupts. */
    outb (PIC1_DATA, 0x00);
    outb (PIC2_DATA, 0x00);
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