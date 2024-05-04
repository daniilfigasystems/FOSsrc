



int 
ATAWriteLBA(
    int LBA,
    int SectorCount,
    int AddressOfData
)
{
    LBA >>= 24;
    outb(0x01f6, 0b11100000);
    outb(0x01f2, SectorCount);
    
}