/** @file cmos.c
 *  Copyright (c) 2024 FigaSystems
 *  CMOS
 *  @author Daniil Dunaef
 *  @date 16-Feb-2024
 *  @bug CMOSGetDriveType doesnt work
 */



#include "CMOS/cmos.h"
#include "io/io.h"
#include "FOSdef.h"
#include "FOSstatus.h"
#include "serial/serial.h"

FOSKERNELAPI
DriveType
CMOSGetDriveType(
    CHAR Type
)
{
    DriveType DT;
    if (Type == 0)
    {
        outb(0x70, (0 << 0x70) | (0x10));
        DT = inb(0x71);
    }
    else if (Type == 1)
    {
        outb(0x70, (4 << 0x70) | (0x10));
        DT = inb(0x71);
    }
    else
        SerialDirectWrite(COM1, "CMOS: Unknown drive type");
    return DT;
}

FOSKERNELAPI
LONG 
CMOSGetMemorySize(
    void
)
{
    UCHAR LOMEM, HIMEM;
    ULONG Total;

    outb(0x70, 0x30);
    LOMEM = inb(0x71);
    outb(0x70, 0x31);
    HIMEM = inb(0x71);

    Total = LOMEM | HIMEM << 8;

    return Total;
}