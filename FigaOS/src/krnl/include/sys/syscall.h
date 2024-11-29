/** @file syscall.h
 *  Copyright (c) 2024 FigaSystems
 *  Syscall implementation
 *  @author Daniil Dunaef
 *  @date 20-Nov-2024
 *  @bug No current bugs found
*/



#ifndef _SYSCALL_
#define _SYSCALL_

#include "FOSdef.h"
#include "regs/regs.h"

#define SYSOPEN 0
#define SYSCLOSE 1
#define SYSREAD 2
#define SYSWRITE 3
#define SYSSEEK 4
#define SYSWAIT 5

VOID
FOSKERNELAPI
SCHandler(
    regs *Registers
);

VOID
FOSKERNELAPI
SCSyscall(
    regs *Registers
);

VOID
FOSKERNELAPI
SCInit(
    void
);

#endif /* !_SYSCALL_! */