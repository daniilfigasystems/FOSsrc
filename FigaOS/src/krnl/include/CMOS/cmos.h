/** @file cmos.h
 *  Copyright (c) 2024 FigaSystems
 *  CMOS
 *  @author Daniil Dunaef
 *  @date 16-Feb-2024
 *  @bug CMOSGetDriveType doesnt work
 */



#ifndef _CMOS_
#define _CMOS_

#include "FOSdef.h"
#include "FOSstatus.h"

typedef enum _DriveType
{
    NoDrive = 0x00,
    Drive360KB5 = 0x01,
    Drive1D2MB5 = 0x02,
    Drive720KB3 = 0x03,
    Drive1D44MB3 = 0x04,
    Drive2D88MB3 = 0x05
} DriveType;

FOSKERNELAPI
DriveType
CMOSGetDriveType(
    CHAR Type
);

FOSKERNELAPI
LONG 
CMOSGetMemorySize(
    void
);

#endif /* !_CMOS_! */