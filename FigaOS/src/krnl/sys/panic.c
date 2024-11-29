/** @file bugcheck.c
 *  Copyright (c) 2023 FigaSystems
 *  Bug tracing and death screen functions
 *  @author Daniil Dunaef
 *  @date 17-Dec-2023
 *  @bug No current bugs found
*/



#include "check/bugcheck.h"
#include "FOSdef.h"
#include "check/bugcodes.h"
#include "regs/regs.h"
#include "timers/pit/pit.h"
#include "timers/pic/pic.h"
#include "CMOS/cmos.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "mm/mm.h"
#include "keyboard/keybps2.h"
#include "isr/isr.h"
#include "debug/debug.h"
#include "irq/irq.h"
#include "BIOS/boot.h"
#include "misc/kprintf.h"

FOSKERNELAPI 
VOID
BCPanic(
    IN ULONG Code,
    IN PCHAR Message
)
{
    dump();
    // If you are getting death screen, dont worry this happens to everyone
    switch(Code)
    {
        case FATAL_UNHANDLED_KERNEL_EXPECTION:
           kprintf("Fatal unhandled kernel exception: %s\n", Message); 
    }
    kprintf("Kernel trap: %s\n", Message);
    kprintf("Code: 0x%x\n", Code);
    kprintf("Registers:\nEAX %d EBX %d ECX %d EDX %d\nESI %d EDI %d EBP %d ESP %d\n", getregs().eax, getregs().ebx, getregs().ecx, getregs().edx, getregs().esi, getregs().edi, getregs().ebp, getregs().esp);
    kprintf("EIP 0x%x\n", getregs().eip);
    kprintf("INT_NO 0x%x\n", getregs().int_no);
    kprintf("EFLAGS 0x%x\n", getregs().eflags);
    // kprintf("GDT: 0x%x IDT: 0x%x", GDT)
    kprintf("Memory free: %dB\n", MMGetFreeMem());
    kprintf("Memory: %dB\n", CMOSGetMemorySize()*1024);
    kprintf("Timer: %d\n", PITGetTimer());
    DBGStackTrace(16);
    kprintf("System Halted\n");

    for (int i = 0; i < 16; i++)
        IRQUninstall(i);
    for (int i = 0; i < 31; i++)
        ISRUninstall(i);

    asm("cli");
    for(;;)
        ;
}