#ifndef _IRQ_
#define _IRQ_

#include "FOSdef.h"

struct irqr {
  //  uint32 ds; /* Data segment selector */ // Removed as suggested by one of the commenters in the previous post (grateful for all the things you pointed out)
   unsigned int gs, fs, ds, es;
   unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pushad. */
   unsigned int int_no, err_code; /* Interrupt number and error code (if applicable) */
   unsigned int eip, cs, eflags; /* Pushed by the processor automatically */
} __attribute__((packed));

FOSKERNELAPI
VOID
IRQInitialize(
    void
);

FOSKERNELAPI
VOID
IRQInstall(
    int IRQ,
    void* Handler
);

FOSKERNELAPI
VOID
IRQUninstall(
    int IRQ
);

#endif /* !_IRQ_! */