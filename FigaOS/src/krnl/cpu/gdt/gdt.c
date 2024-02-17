/** @file gdt.c
 *  Copyright (c) 2023 FigaSystems
 *  Global descriptor table
 *  @author Daniil Dunaef
 *  @date 16-Nov-2023
 *  @bug No current bugs found
*/



#include "gdt/gdt.h"
#include "FOSdef.h"
#include "check/bugcheck.h"

struct gdt_entry gdt[6];
struct gdt_pointer gp;

FOSKERNELAPI
VOID
GDTSetGate(
    int num, 
    unsigned long base, 
    unsigned long limit, 
    unsigned char access, 
    unsigned char granularity
)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].limit_middle = (limit >> 16) & 0xFF;
    gdt[num].limit_high = (limit >> 24) & 0xFF;
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (granularity & 0xF0);
    gdt[num].access = access;
}

FOSKERNELAPI
VOID
GDTInstall(
    void
)
{
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (unsigned int) &gdt;

    GDTSetGate(0,0,0,0,0);
    asm volatile ("lgdt %0" :: "m"(gp));

    if (gp.base == 0)
    {
        KeBugCheck(FATAL_UNHANDLED_KERNEL_EXPECTION);

    }
}