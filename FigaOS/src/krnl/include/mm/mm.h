/** @file mm.h
 *  Copyright (c) 2023 FigaSystems
 *  Memory Management
 *  @author Daniil Dunaef
 *  @date 3-Mar-2024
 *  @bug No current bugs found
*/



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

CHAR
*
FOSKERNELAPI
MMAllocatePool(
    MemorySize SizeOfMemory
);

int
FOSKERNELAPI
MMGetFreeMem(
    void
);

#endif /* !_MM_! */