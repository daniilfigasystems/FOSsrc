/** @file v86.c
 *  Copyright (c) 2024 FigaSystems
 *  Virtual 8086 mode
 *  @author Daniil Dunaef
 *  @date 1-Jul-2024
 *  @bug No current bugs found
*/



#include "v86/v86.h"
#include "misc/kprintf.h"
#include "libs/headers/string.h"
#include "regs/regs.h"
#include "FOSdef.h"

regs V86Regs;

extern void V86Enter(regs *r);

FOSKERNELAPI
VOID
V86Initialize(
    void
)
{
    memset(&V86Regs, 0, sizeof(regs));

    V86Enter(&V86Regs);
}

VOID
V86GetRegs(regs *r)
{
    memcpy(r, &V86Regs, sizeof(regs));
}