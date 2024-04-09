#include "BIOS/boot.h"
#include "timers/pic/pic.h"
#include "idt/idt.h"
#include "irq/irq.h"
#include "io/io.h"
#include "misc/kprintf.h"



void
ISRHandler(
    void
)
{
    
}

void
INT32Handler(
    void
)
{
    PICSendEOI(0);
}

void
INT33Handler(
    void
)
{
    PICSendEOI(1);
    unsigned char ch = inb(0x60);
    kprintf("key");
}

