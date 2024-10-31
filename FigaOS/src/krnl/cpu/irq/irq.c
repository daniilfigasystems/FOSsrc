/** @file irq.c
 *  Copyright (c) 2023 FigaSystems
 *  IRQ (Interrupt Request)
 *  @author Daniil Dunaef
 *  @date 3-Mar-2024
 *  @bug No current bugs found
*/



#include "irq/irq.h"
#include "FOSdef.h"
#include "FOSstatus.h"
#include "idt/idt.h"
#include "misc/kprintf.h"
#include "serial/serial.h"
#include "regs/regs.h"
#include "io/io.h"
#include "timers/pic/pic.h"

int IRQLast;

extern VOID _irq0();
extern VOID _irq1();
extern VOID _irq2();
extern VOID _irq3();
extern VOID _irq4();
extern VOID _irq5();
extern VOID _irq6();
extern VOID _irq7();
extern VOID _irq8();
extern VOID _irq9();
extern VOID _irq10();
extern VOID _irq11();
extern VOID _irq12();
extern VOID _irq13();
extern VOID _irq14();
extern VOID _irq15();

void* IRQRoutines[16] =
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

FOSKERNELAPI
INT
IRQWaitForInterrupt(
    INT InterruptNumber
)
{
    while(IRQLast != InterruptNumber)
        ;;
    return IRQLast;
}

FOSKERNELAPI
VOID
IRQHandler(
    struct irqr* registers
)
{
    void (*handler)(struct irqr* r);
	handler = IRQRoutines[registers->int_no];
    IRQLast = registers->int_no;

	if (handler)
		handler(registers);

	if (registers->int_no >= 8)
		outb(0xA0, 0x20);

	outb(0x20, 0x20);
}

FOSKERNELAPI
VOID
IRQGatesInstall(
    void
)
{
    IDTSetGate(32, (unsigned)_irq0, 0x08, 0x8E);
    IDTSetGate(33, (unsigned)_irq1, 0x08, 0x8E);
    IDTSetGate(34, (unsigned)_irq2, 0x08, 0x8E);
    IDTSetGate(35, (unsigned)_irq3, 0x08, 0x8E);
    IDTSetGate(36, (unsigned)_irq4, 0x08, 0x8E);
    IDTSetGate(37, (unsigned)_irq5, 0x08, 0x8E);
    IDTSetGate(38, (unsigned)_irq6, 0x08, 0x8E);
    IDTSetGate(39, (unsigned)_irq7, 0x08, 0x8E);
    IDTSetGate(40, (unsigned)_irq8, 0x08, 0x8E);
    IDTSetGate(41, (unsigned)_irq9, 0x08, 0x8E);
    IDTSetGate(42, (unsigned)_irq10, 0x08, 0x8E);
    IDTSetGate(43, (unsigned)_irq11, 0x08, 0x8E);
    IDTSetGate(44, (unsigned)_irq12, 0x08, 0x8E);
    IDTSetGate(45, (unsigned)_irq13, 0x08, 0x8E);
    IDTSetGate(46, (unsigned)_irq14, 0x08, 0x8E);
    IDTSetGate(47, (unsigned)_irq15, 0x08, 0x8E);
}

FOSKERNELAPI
VOID
IRQInitialize(
    void
)
{
    PICRemap();
    IRQGatesInstall();
}

FOSKERNELAPI
VOID
IRQInstall(
    int IRQ,
    void* Handler
)
{
    IRQRoutines[IRQ] = Handler;
}

FOSKERNELAPI
VOID
IRQUninstall(
    int IRQ
)
{
    IRQRoutines[IRQ] = 0;
}