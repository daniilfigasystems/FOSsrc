


#ifndef _PAGING_
#define _PAGING_

#include "FOSdef.h"

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
);

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
);

FOSKERNELAPI
VOID
PGIdPaging(
    PUINT PageTableAddress,
    INT From,
    INT Size
);

FOSKERNELAPI
PVOID
PGGetPhysicalAddress(
    PVOID VirtualAddress
);

FOSKERNELAPI
VOID
PGReallocateKernel(
    ULONG KernelAddress
);

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
);

FOSKERNELAPI
VOID
PGInitializePaging(
    VOID
);

#endif /* !_PAGING_! */