#include "rand/rand.h"
#include "misc/kprintf.h"
#include "regs/regs.h"
#include "timers/pit/pit.h"
#include "FOSdef.h"

extern checkRDRAND();
extern checkRDSEED();

RNDType RandomType;

INT 
RNDInitRandom(
    void
)
{

}

VOID
RNDGetRandom(
    regs registers
)
{
    if (registers.ecx)
        RandomType = RDRAND;
    else if (registers.ebx)
        RandomType = RDSEED;
    else
        RandomType = SRAND;
}

INT
RNDRandom(
    void
)
{
    int num = 0;
    switch(RandomType)
    {
        case RDRAND:
            asm("rdrand %0" : "=r"(num));
        break;
        case RDSEED:
            asm("rdseed %0" : "=r"(num));
        break;
        case SRAND:
            PIT
        break;
    }
}