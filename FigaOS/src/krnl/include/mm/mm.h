#ifndef _MM_
#define _MM_

#include "FOSdef.h"
#include "FOSstatus.h"

typedef INT PageSize;
typedef LONG MemorySize;
typedef LONG HeapSize;
typedef LONG MemoryAddress;

typedef struct _MemoryBlock
{
    PageSize Size;
    MemoryAddress Address;
    BOOL IsFree;
} MemoryBlock;

typedef struct _ExtendedMemoryBlock
{
    MemorySize Size;
    MemoryAddress Address;
    BOOL IsFree;
} ExtendedMemoryBlock;

typedef struct _HeapBlock
{
    HeapSize Size;
    MemoryAddress HeapStart;
    MemoryAddress HeapEnd;
} HeapBlock;

VOID
FOSKERNELAPI
MMInitializeMemory(
    MemoryAddress KernelEntry,
    MemorySize SizeOfMemory
);

MemoryBlock
FOSKERNELAPI
MMAllocatePool(
    MemorySize SizeOfMemory
);

#endif /* !_MM_! */