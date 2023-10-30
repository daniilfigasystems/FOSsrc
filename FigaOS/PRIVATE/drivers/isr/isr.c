#include "regs.h"
#include "isr.h"
#include "serial.h"
#include "idt.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr8();
extern void isr14();
extern void isr30();

void isrs_install()
{
    idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned)isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned)isr2, 0x08, 0x8E);

 
    idt_set_gate(8, (unsigned)isr8, 0x08, 0x8E);
    idt_set_gate(14, (unsigned)isr14, 0x08, 0x8E);
    idt_set_gate(30, (unsigned)isr30, 0x08, 0x8E);
    write_com(0x3f8, " isr installed ");
}


unsigned char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound range exceeded",
    "Invalid opcode",
    "Device Not Available",
    "Double Fault",
};



void fault_handler(struct regs *r)
{
    
    if (r->int_no < 32)
    {
        
       
        for (;;);
    }
}