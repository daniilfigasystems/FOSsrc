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
#include <libs/headers/string.h>
#include "FOSdef.h"
#include "FOSstatus.h"

MemorySize MemSize = 0;
HeapBlock HeapKernelBlock;
HeapBlock PageHeap;
unsigned char *PageHeapDesc = 0;
MemorySize MemFree = 0;
MemorySize MemUsed = 0;

MemoryAddress LastAllocatedAddress = 0;
MemorySize LastAllocatedSize = 0;


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

    LastAllocatedAddress = KernelEntry + 0x1000;

    PageHeap.HeapEnd = 0x400000;
    PageHeap.HeapStart = PageHeap.HeapEnd - (32 * 4096);

    HeapKernelBlock.HeapStart = LastAllocatedAddress;
    HeapKernelBlock.HeapEnd = PageHeap.HeapStart;
    
    LastAllocatedSize = HeapKernelBlock.HeapEnd - HeapKernelBlock.HeapStart;
    MemFree -= HeapKernelBlock.Size;
    PageHeapDesc = (unsigned char*) MMAllocatePool(32);
}

CHAR
*
FOSKERNELAPI
MMAllocatePool(
    MemorySize SizeOfMemory
)
{
    if (SizeOfMemory > 0)
    {
        if (LastAllocatedAddress < MemSize)
        {
            PUCHAR Memory = (PUCHAR)HeapKernelBlock.HeapStart;

            while ((PUCHAR)Memory < LastAllocatedAddress)
            {
                MemoryBlock *MBlock = (MemoryBlock*)Memory;
                
                if (!MBlock->Size)
                    goto Nalloc;
                
                if (!MBlock->IsFree)
                {
                    Memory += MBlock->Size;
                    Memory += sizeof(MemoryBlock);
                    Memory += 4;
                    continue;
                }

                if (MBlock->Size >= SizeOfMemory)
                {
                    MBlock->IsFree = 0;

                    memset(Memory + sizeof(MemoryBlock), 0, SizeOfMemory);
                    MemUsed += SizeOfMemory + sizeof(MemoryBlock);
                    return (PUCHAR)(Memory + sizeof(MemoryBlock));
                }

                Memory += MBlock->Size;
                Memory += sizeof(MemoryBlock);
                Memory += 4;
            }

	        Nalloc:;
	        if(LastAllocatedAddress+SizeOfMemory+sizeof(MemoryBlock) >= HeapKernelBlock.HeapEnd)
	        {
                kprintf("Cannot alloc: Out of memory!\n");
	        }
	        MemoryBlock *MBlock = (MemoryBlock*) LastAllocatedAddress;
	        MBlock->IsFree = 0;
	        MBlock->Size = SizeOfMemory;

	        LastAllocatedAddress += SizeOfMemory;
	        LastAllocatedAddress += sizeof(MemoryBlock);
	        LastAllocatedAddress += 4;

            kprintf("Allocated %d bytes from 0x%x to 0x%x\n", SizeOfMemory, (UINT) MBlock + sizeof(MemoryBlock), LastAllocatedAddress);

	        MemUsed += SizeOfMemory + 4 + sizeof(MemoryBlock);
	        memset((PUCHAR)((UINT)MBlock + sizeof(MemoryBlock)), 0, SizeOfMemory);
	        return (PUCHAR)((UINT)MBlock + sizeof(MemoryBlock));
        }
        else
            kprintf("MM: Failed to allocate pool\n");
    }
    else
        kprintf("Memory Error : Memory size must be greater than zero\n");
}

VOID
FOSKERNELAPI
MMFreePool(
    void *Memory
)
{
    MemoryBlock *MBlock = (Memory - sizeof(MemoryBlock));
    MemUsed -= MBlock->Size + sizeof(MemoryBlock);
    MBlock->IsFree = 1;
}

int
FOSKERNELAPI
MMGetFreeMem(
    void
)
{
    return MemFree;
}