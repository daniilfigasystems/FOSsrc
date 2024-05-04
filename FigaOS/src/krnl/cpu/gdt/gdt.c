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

extern void GDTi();

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
	gdt[num].granularity = (limit >> 16) & 0x0F;

	gdt[num].granularity |= (granularity & 0xF0);

	gdt[num].access = access;
}

FOSKERNELAPI
VOID
GDTInstall(
    void
)
{
    gp.limit = (sizeof(struct gdt_entry) * 6) - 1;
    gp.base = (unsigned int) &gdt;

    // TODO: Implement code for setting up the GDT entries
    // The first entry is a null descriptor (ignored)
    GDTSetGate(0, 0, 0, 0, 0);
    // The second entry is a code segment descriptor
    // with a limit of 0xFFFFFFFF (4GB) and a base of 0.
    // The access byte is 0x9A, indicating a 4-byte
    // (32-bit) code segment with the accessed flag set.
    // The granularity flag is set to its maximum value
    // of 1, indicating that the segment is 4KB granular.
    GDTSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // The third entry is a data segment descriptor
    // with a limit of 0xFFFFFFFF (4GB) and a base of 0.
    // The access byte is 0x9F, indicating a 4-byte
    // (32-bit) data segment with the accessed flag set.
    // The granularity flag is set to its maximum value
    // of 1, indicating that the segment is 4KB granular.
    GDTSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    GDTSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    GDTSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    if (gp.base == 0)
    {
        KeBugCheck(FATAL_UNHANDLED_KERNEL_EXPECTION);

    }
    GDTi();
}