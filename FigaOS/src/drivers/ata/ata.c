#include "ata/ide.h"
#include "io/io.h"
#include "misc/kprintf.h"

int 
IDEWriteLBA(
    int LBA,
    int SectorCount,
    int AddressOfData
)
{
    LBA >>= 24;
    outb(0x01f6, 0b11100000);
    outb(0x01f2, SectorCount);
    
}

void IDELToC(
    int LBA,
    int *Head,
    int *Track,
    int *Sector
)
{
    (*Head) = (LBA % (63 * 2)) / 63;
    (*Track) = (LBA / (63 * 2));
    (*Sector) = (LBA % 63 + 1);
}