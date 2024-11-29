/** @file syscall.c
 *  Copyright (c) 2024 FigaSystems
 *  Syscall implementation
 *  @author Daniil Dunaef
 *  @date 20-Nov-2024
 *  @bug No current bugs found
*/



#include "sys/syscall.h"
#include "misc/kprintf.h"
#include "check/bugcheck.h"
#include "check/bugcodes.h"
#include "regs/regs.h"
#include "idt/idt.h"
#include "isr/isr.h"
#include "timers/pit/pit.h"
#include "FOSdef.h"

extern void SCSyscallHandler(void);
extern void SCDoSyscall(regs *Registers);

VOID
FOSKERNELAPI
SCHandler(
    regs *Registers
)
{
    switch(Registers->eax)
    {
        case SYSOPEN:
        break;
        case SYSCLOSE:
        break;
        case SYSREAD:
        break;
        case SYSWRITE:
            if (Registers->edi == 1)
            {
                for (int i = 0; i < Registers->ecx; i++)
                {
                    kprintf("%c", (CHAR)Registers->esi + i);  
                }
            }
        break;
        case SYSSEEK:
        break;
        case SYSWAIT:
            wait(Registers->ebx);
        break;
    }
}

VOID
FOSKERNELAPI
SCSyscall(
    regs *Registers
)
{
    SCDoSyscall(Registers);
}

VOID
FOSKERNELAPI
SCInit(
    void
)
{
     ISRInstall(0x7F, &SCSyscallHandler);
}