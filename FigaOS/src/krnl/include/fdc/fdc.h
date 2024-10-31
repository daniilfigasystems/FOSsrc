#ifndef _FDC_
#define _FDC_

#include "regs/regs.h"
#include "FOSdef.h"
#include "FOSstatus.h"

#define FDC_STATUS_A 0x3f0 // READ ONLY
#define FDC_STATUS_B 0x3f1 // READ ONLY
#define FDC_DIGITAL_OUT 0x3f2
#define FDC_TAPE_DRIVE 0x3f3
#define FDC_MAIN_STATUS 0x3f4 // READ ONLY
#define FDC_DATARATE_SEL 0x3f4 // WRITE ONLY
#define FDC_DATA_FIFO 0x3f5
#define FDC_DIGITAL_IN 0x3f7 // READ ONLY
#define FDC_CONF_CONTROL 0x3f7 // WRITE ONLY

#define FDC_DOR_MOT_A_ON 0x1c
#define FDC_DOR_MOT_A_OFF 0x0c
#define FDC_DOR_RESET 0x00

#define FDC_MSR_BUSY 0x10
#define FDC_MSR_RQM  0x80

#define FDC_READ_TRACK 0x2
#define FDC_SPECIFY 0x3
#define FDC_SENSE_DRIVE_STATUS 0x4
#define FDC_WRITE_DATA 0x5
#define FDC_READ_DATA 0x6
#define FDC_RECALIBRATE 0x7
#define FDC_SENSE_INTERRUPT 0x8
#define FDC_SEEK 0xf
#define FDC_VERIFY 0x16

#define STATUS_NO_DISK ((FOSSTATUS)0xCF00000FL)

typedef 
enum
_FDCDirection
{
    FDC_Dir_Read = 1,
    FDC_Dir_Write = 2
} FDCDirection;

FOSKERNELAPI
VOID
FDCHandler(
    regs *Registers
);

FOSKERNELAPI
VOID
FDCLToC(
    INT LBA, 
    PUSHORT Cylinder, 
    PUSHORT Head, 
    PUSHORT Sector
);

FOSKERNELAPI
VOID
FDCWait(
    void
);

FOSKERNELAPI
BOOL
FDCIsReady(
    void
);

FOSKERNELAPI
BOOL
FDCWaitUntilReady(
    void
);

FOSKERNELAPI
FOSSTATUS
FDCSeekTrackSide(
    UCHAR Track,
    UCHAR Side
);

FOSKERNELAPI
FOSSTATUS
FDCSeek(
    int Base,
    UINT Cylinder,
    int Head
);

FOSKERNELAPI
FOSSTATUS
FDCDoTrack(
    int Base,
    unsigned Cylinder,
    FDCDirection Direction
);

FOSKERNELAPI
CHAR
FDCGetDMAByte(
    long Bytes
);

FOSKERNELAPI
FOSSTATUS
FDCSendByte(
    char Byte
);

FOSKERNELAPI
INT
FDCReceiveByte(
    void
);

FOSKERNELAPI
VOID
FDCRecalibrate(
    int DriveType
);

FOSKERNELAPI
VOID
FDCMotorON(
    int DriveType
);

FOSKERNELAPI
VOID
FDCMotorOFF(
    int DriveType
);

FOSKERNELAPI
FOSSTATUS
FDCReset(
    int DriveType
);

FOSKERNELAPI
VOID
FDCPrepareDMAWrite(
    void
);

FOSKERNELAPI
VOID
FDCPrepareDMARead(
    void
);

FOSKERNELAPI
VOID
FDCInitDMA(
    FDCDirection Direction
);

FOSKERNELAPI
VOID
FDCInit(
    int DriveType
);

#endif /* !_FDC_! */