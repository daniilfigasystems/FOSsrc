#include "regs/regs.h"

regs global_regs;

void __dump_dummy__(regs registers)
{
   memcpy(&global_regs, &registers, sizeof(registers));
}

extern void dump();
// {
    // asm volatile("pusha; call __dump_dummy__; popa");
// }

regs getregs()
{
    return global_regs;
}