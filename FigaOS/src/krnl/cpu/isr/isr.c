#include "isr/irs.h"
#include "BIOS/boot.h"
#include "timers/pic/pic.h"
#include "idt/idt.h"
#include "irq/irq.h"
#include "io/io.h"
#include "misc/kprintf.h"

extern void isr_0();
extern void isr_1();
extern void isr_2();
extern void isr_3();
extern void isr_4();
extern void isr_5();
extern void isr_6();
extern void isr_7();
extern void isr_8();
extern void isr_9();
extern void isr_10();
extern void isr_11();
extern void isr_12();
extern void isr_13();
extern void isr_14();
extern void isr_15();
extern void isr_16();
extern void isr_17();
extern void isr_18();
extern void isr_19();
extern void isr_20();
extern void isr_21();
extern void isr_22();
extern void isr_23();
extern void isr_24();
extern void isr_25();
extern void isr_26();
extern void isr_27();
extern void isr_28();
extern void isr_29();
extern void isr_30();
extern void isr_31();

static void *ISRRoutines[32] = { NULL };

void ISRInstall(int isrs, void* handler)
{
	ISRRoutines[isrs] = handler;
}

void ISRUninstall(int isrs)
{
	ISRRoutines[isrs] = 0;
}


void ISRInit()
{
	IDTSetGate(0, (unsigned)isr_0, 0x08, 0x8E);
	IDTSetGate(1, (unsigned)isr_1, 0x08, 0x8E);
	IDTSetGate(2, (unsigned)isr_2, 0x08, 0x8E);
	IDTSetGate(3, (unsigned)isr_3, 0x08, 0x8E);
	IDTSetGate(4, (unsigned)isr_4, 0x08, 0x8E);
	IDTSetGate(5, (unsigned)isr_5, 0x08, 0x8E);
	IDTSetGate(6, (unsigned)isr_6, 0x08, 0x8E);
	IDTSetGate(7, (unsigned)isr_7, 0x08, 0x8E);
	IDTSetGate(8, (unsigned)isr_8, 0x08, 0x8E);
	IDTSetGate(9, (unsigned)isr_9, 0x08, 0x8E);
	IDTSetGate(10, (unsigned)isr_10, 0x08, 0x8E);
	IDTSetGate(11, (unsigned)isr_11, 0x08, 0x8E);
	IDTSetGate(12, (unsigned)isr_12, 0x08, 0x8E);
	IDTSetGate(13, (unsigned)isr_13, 0x08, 0x8E);
	IDTSetGate(14, (unsigned)isr_14, 0x08, 0x8E);
	IDTSetGate(15, (unsigned)isr_15, 0x08, 0x8E);
	IDTSetGate(16, (unsigned)isr_16, 0x08, 0x8E);
	IDTSetGate(17, (unsigned)isr_17, 0x08, 0x8E);
	IDTSetGate(18, (unsigned)isr_18, 0x08, 0x8E);
	IDTSetGate(19, (unsigned)isr_19, 0x08, 0x8E);
	IDTSetGate(20, (unsigned)isr_20, 0x08, 0x8E);
	IDTSetGate(21, (unsigned)isr_21, 0x08, 0x8E);
	IDTSetGate(22, (unsigned)isr_22, 0x08, 0x8E);
	IDTSetGate(23, (unsigned)isr_23, 0x08, 0x8E);
	IDTSetGate(24, (unsigned)isr_24, 0x08, 0x8E);
	IDTSetGate(25, (unsigned)isr_25, 0x08, 0x8E);
	IDTSetGate(26, (unsigned)isr_26, 0x08, 0x8E);
	IDTSetGate(27, (unsigned)isr_27, 0x08, 0x8E);
	IDTSetGate(28, (unsigned)isr_28, 0x08, 0x8E);
	IDTSetGate(29, (unsigned)isr_29, 0x08, 0x8E);
	IDTSetGate(30, (unsigned)isr_30, 0x08, 0x8E);
	IDTSetGate(31, (unsigned)isr_31, 0x08, 0x8E);
}

void ISRHandle(struct irqr* r)
{
	if (r->int_no < 32)
	{
		void (*handler)(struct regs_t* r);
		handler = ISRRoutines[r->int_no];

		if (handler)
			handler(r);
		else
		{
            kprintf("filt");
		}
	}
}