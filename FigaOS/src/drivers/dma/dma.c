


#include "dma/dma.h"
#include "io/io.h"
#include "misc/kprintf.h"
#include "FOSdef.h"

int DMAMasks;

FOSKERNELAPI
VOID
DMAMask(
    INT Channel
)
{
    DMAMasks |= (1 << Channel);
    if (Channel >=4 )
        outb(0xde, DMAMasks >> 4);
    else
        outb(0x0f, DMAMasks & 0x0f);
}

FOSKERNELAPI
VOID
DMAUnMask(
    INT Channel
)
{
    DMAMasks &= (~(1 << Channel));
    if (Channel >= 4)
        outb(0xde, DMAMasks >> 4);
    else
        outb(0x0f, DMAMasks & 0x0f);
}

FOSKERNELAPI
VOID
DMAClearTrigger(
    INT Channel
)
{
    if (Channel < 4)
        outb(0x0c, 0xaa);
    else
        outb(0xd8, 0xaa);
}

FOSKERNELAPI
VOID
DMASetWorkMode(
    INT Channel,
    INT WorkMode
)
{
    int chan = Channel & 0x07; 

    if (chan < 4)
        outb(0x0b, ((WorkMode & 0xfc) | (chan & 0x3)));
    else
        outb(0xd6, ((WorkMode & 0xfc) | (chan & 0x3)));
}

FOSKERNELAPI
VOID
DMASetBufferAddr2(
    INT Address
)
{
    outb(0x04, Address);
    outb(0x04, Address >> 8);
    outb(0x81, Address >> 16);
}

FOSKERNELAPI
VOID
DMASetCycles2(
    INT Cycles
)
{
    int counter=Cycles-1;

    outb(0x05, counter);
    outb(0x05, counter >> 8);
}

FOSKERNELAPI
VOID
DMAResetFlipFlop(
    INT Channel
)
{
    if (Channel < 4)
        outb(0x0c, 0xff);
    else
        outb(0xd8, 0xff);
}