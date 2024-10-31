#ifndef _DMA_
#define _DMA_

#include "FOSdef.h"

FOSKERNELAPI
VOID
DMAMask(
    INT Channel
);

FOSKERNELAPI
VOID
DMAUnMask(
    INT Channel
);

FOSKERNELAPI
VOID
DMAClearTrigger(
    INT Channel
);

FOSKERNELAPI
VOID
DMASetWorkMode(
    INT Channel,
    INT WorkMode
);

FOSKERNELAPI
VOID
DMASetBufferAddr2(
    INT Address
);

FOSKERNELAPI
VOID
DMASetCycles2(
    INT Cycles
);

FOSKERNELAPI
VOID
DMAResetFlipFlop(
    INT Channel
);

#endif /* !_DMA_! */