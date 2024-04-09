/** @file mm.c
 *  Copyright (c) 2023 FigaSystems
 *  Memory Management
 *  @author Daniil Dunaef
 *  @date 3-Mar-2024
 *  @bug No current bugs found
*/



#include "mm/mm.h"
#include "serial/serial.h"
#include "misc/kprintf.h"
#include "FOSdef.h"
#include "FOSstatus.h"

MemorySize MemSize = 0;
HeapBlock HeapKernelBlock;
MemorySize MemFree = 0;

MemoryBlock LastAllocated;
MemoryAddress LastAllocatedAddress = 0;


VOID
FOSKERNELAPI
MMInitializeMemory(
    MemoryAddress KernelEntry,
    MemorySize SizeOfMemory
)
{
    if (SizeOfMemory > 0)
        MemSize = SizeOfMemory;
    else
        kprintf("Memory Error : Memory size must be greater than zero\n");

    MemFree = MemSize;

    LastAllocatedAddress = KernelEntry;

    HeapKernelBlock.HeapStart = LastAllocatedAddress;
    HeapKernelBlock.HeapEnd = 0x3e0000;

    LastAllocated.Address = LastAllocatedAddress;
    
    if (LastAllocated.Size > 0)
        LastAllocated.IsFree = false;
    else
        LastAllocated.IsFree = true;
    
    LastAllocated.Size = HeapKernelBlock.HeapEnd;
    MemFree -= HeapKernelBlock.Size;
    kprintf("Last Allocated Address: %d\n", LastAllocated.Address);
    kprintf("Free Memory: %dKB\n", MemFree);
}

MemoryBlock
FOSKERNELAPI
MMAllocatePool(
    MemorySize SizeOfMemory
)
{
    if (SizeOfMemory > 0)
    {
        if (LastAllocatedAddress < MemSize)
        {
            MemoryBlock MemPool;
            MemPool.Size = SizeOfMemory;
            MemPool.Address = LastAllocatedAddress + SizeOfMemory;
            MemPool.IsFree = true;
            LastAllocated = MemPool;
            LastAllocatedAddress = MemPool.Address;
            MemFree -= MemPool.Size;
            return MemPool;
        }
        else
            kprintf("MM: Failed to allocate pool\n");
    }
    else
        kprintf("Memory Error : Memory size must be greater than zero\n");
}

int
FOSKERNELAPI
MMGetFreeMem(
    void
)
{
    return MemFree;
}