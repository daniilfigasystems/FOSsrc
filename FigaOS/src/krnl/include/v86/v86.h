/** @file v86.h
 *  Copyright (c) 2024 FigaSystems
 *  Virtual 8086 mode
 *  @author Daniil Dunaef
 *  @date 2-Jul-2024
 *  @bug No current bugs found
*/

#ifndef _V86_
#define _V86_

#include "regs/regs.h"
#include "FOSdef.h"

FOSKERNELAPI
VOID
V86Initialize(
    void
);

VOID
V86GetRegs(
    regs *r
);

#endif /* !_V86_! */