

#include "mm/mm.h"
#include "serial/serial.h"
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
        SerialDirectWrite(COM1, "Memory Error : Memory size must be greater than zero");

    LastAllocatedAddress = KernelEntry;

    HeapKernelBlock.HeapStart = LastAllocatedAddress;
    HeapKernelBlock.HeapEnd = HeapKernelBlock.HeapStart + SizeOfMemory;

    LastAllocated.Address = LastAllocatedAddress;
    
    if (LastAllocated.Size > 0)
        LastAllocated.IsFree = false;
    else
        LastAllocated.IsFree = true;
    
    LastAllocated.Size = HeapKernelBlock.HeapEnd;
    MemFree += HeapKernelBlock.Size;
    SerialDirectWrite(COM1, "Last Allocated Address");
    SerialDirectWrite(COM1, LastAllocated.Address);
}

MemoryBlock
FOSKERNELAPI
MMAllocatePool(
    MemorySize SizeOfMemory
)
{
    if (SizeOfMemory > 0)
    {
        if (LastAllocatedAddress < HeapKernelBlock.HeapEnd)
        {
            MemoryBlock MemPool;
            MemPool.Size = SizeOfMemory;
            MemPool.Address = LastAllocatedAddress + SizeOfMemory;
            MemPool.IsFree = true;
            LastAllocated = MemPool;
            LastAllocatedAddress = MemPool.Address;
            return MemPool;
        }
        else
            SerialDirectWrite(COM1, "MM: Failed to allocate pool");
    }
    else
        SerialDirectWrite(COM1, "Memory Error : Memory size must be greater than zero");
}