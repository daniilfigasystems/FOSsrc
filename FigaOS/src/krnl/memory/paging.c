/** @file paging.c
 *  Copyright (c) 2024 FigaSystems
 *  Memory Paging
 *  @author Daniil Dunaef
 *  @date 14-Aug-2024
 *  @bug No current bugs found
*/



#include "mm/paging.h"
#include "isr/isr.h"
#include "regs/regs.h"
#include "check/bugcheck.h"
#include "check/bugcodes.h"
#include "misc/kprintf.h"
#include "FOSdef.h"

extern void PGInstallPageDirectory(unsigned int *PageDirectoryAddress);
extern void PGEnablePaging();

unsigned int PageDirectory[1024] __attribute__((aligned(4096)));
unsigned int PageTable[1024] __attribute((aligned(4096)));
unsigned int PageTableKernel[1024] __attribute((aligned(4096)));

FOSKERNELAPI
VOID
PGHandler(
    regs *Registers
)
{
    unsigned long FaultAddress;

    asm volatile ("mov %%cr2, %0" : "=r" (FaultAddress));

    kprintf("PG: Page Fault!\n");
    kprintf("Bad Address: 0x%x\n Error: %d", FaultAddress, Registers->err_code);

    BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "Page Fault");
}

FOSKERNELAPI
VOID
PGInitializePageDirectory(
    CHAR Present,
    CHAR ReadWrite,
    CHAR UserSuperior,
    CHAR WriteThrough,
    CHAR CacheDisable,
    CHAR Accessed,
    CHAR PageSize
)
{
    for (int i = 0; i < 1024; i++)
        PageDirectory[i] = Present | ReadWrite << 1 | UserSuperior << 2 | WriteThrough << 3 | CacheDisable << 4 | Accessed << 5 | PageSize << 6;
}

FOSKERNELAPI
VOID
PGInitializePageTable(
    CHAR Present,
    CHAR ReadWrite,
    CHAR UserSuperior,
    CHAR WriteThrough,
    CHAR CacheDisable,
    CHAR Accessed,
    CHAR Dirty,
    CHAR PageAttributeTable,
    CHAR Global
)
{
    for (int i = 0; i < 1024; i++)
        PageTable[i] = (i * 0x1000) | Present | ReadWrite << 1 | UserSuperior << 2 | WriteThrough << 3 | CacheDisable << 4 | Accessed << 5 | Dirty << 6 | PageAttributeTable << 7 | Global << 8;

    PageDirectory[0] |= ((unsigned int)PageTable);
}

FOSKERNELAPI
VOID
PGIdPaging(
    PUINT PageTableAddress,
    INT From,
    INT Size
)
{
    From = From & 0xfffff000;

    for (; Size > 0; From += 4096, Size -= 4096, PageTableAddress++)
        *PageTableAddress = From | 1;
}

FOSKERNELAPI
PVOID
PGGetPhysicalAddress(
    PVOID VirtualAddress
)
{
    unsigned long PageDirectoryIndex = (unsigned long)VirtualAddress >> 22;
    unsigned long PageTableIndex = (unsigned long)VirtualAddress >> 12 & 0x03ff;

    unsigned long *PageDirectoryAddress = (unsigned long *)0xfffff000;
    unsigned long *PageTableAddress = ((unsigned long *)0xffc00000) + (0x400 * PageTableIndex);

    return (void *)((PageTableAddress[PageTableIndex] & ~0xfff) + ((unsigned long)VirtualAddress & 0xfff));
}

FOSKERNELAPI
VOID
PGReallocateKernel(
    ULONG KernelAddress
)
{
    unsigned long KernelAddr = KernelAddress;

    for (int i = 0; i < 1024; i++)
        PageTableKernel[i] = (KernelAddr + (i * 0x1000)) | 3;
    
    PageDirectory[1] |= ((unsigned int)PageTableKernel);
}

FOSKERNELAPI
VOID
PGMapPhysicalMemory(
    PVOID PhysicalAddress,
    PVOID VirtualAddress,
    CHAR Present,
    CHAR ReadWrite,
    CHAR UserSuperior,
    CHAR WriteThrough,
    CHAR CacheDisable,
    CHAR Accessed,
    CHAR Dirty,
    CHAR PageAttributeTable,
    CHAR Global
)
{
    unsigned long PageDirectoryIndex = (unsigned long)VirtualAddress >> 22;
    unsigned long PageTableIndex = (unsigned long)VirtualAddress >> 12 & 0x03ff;

    unsigned long *PageDirectoryAddress = (unsigned long *)0xfffff000;
    unsigned long *PageTableAddress = ((unsigned long *)0xffc00000) + (0x400 * PageTableIndex);

     PageTableAddress[PageTableIndex] = (unsigned long)PhysicalAddress << 11 | Present | ReadWrite << 1 | UserSuperior << 2 | WriteThrough << 3 | CacheDisable << 4 | Accessed << 5 | Dirty << 6 | PageAttributeTable << 7 | Global << 8;
}

FOSKERNELAPI
VOID
PGInitializePaging(
    VOID
)
{
    PGInitializePageDirectory(1, 1, 0, 0, 0, 0, 0);
    PGInitializePageTable(1, 1, 0, 0, 0, 1, 0, 0, 0);

    PGIdPaging(&PageTable, 0x00000000, 0x100000);
    PGReallocateKernel(0x100000);

    ISRInstall(14, PGHandler);

    PGInstallPageDirectory(&PageDirectory);
    PGEnablePaging();
}