/** @file fdc.c
 *  Copyright (c) 2024 FigaSystems
 *  Floppy Disk Controller
 *  @author Daniil Dunaef
 *  @date 10-Aug-2024
 *  @bug No current bugs found
*/



#include "fdc/fdc.h"
#include "CMOS/cmos.h"
#include "io/io.h"
#include "irq/irq.h"
#include "dma/dma.h"
#include "check/bugcheck.h"
#include "check/bugcodes.h"
#include "timers/pit/pit.h"
#include "misc/kprintf.h"
#include "regs/regs.h"
#include "FOSdef.h"
#include "FOSstatus.h"

int FDCInterrupt = 0;

static const char FDCDMABUFF[0x4800] __attribute__((aligned(0x8000)));

FOSKERNELAPI
VOID
FDCHandler(
    regs *Registers
)
{
    FDCInterrupt = 1;
}

FOSKERNELAPI
VOID
FDCLToC(
    INT LBA, 
    PUSHORT Cylinder, 
    PUSHORT Head, 
    PUSHORT Sector
)
{
    *Cylinder = LBA / (2 * 18);
    *Head = ((LBA % (2 * 18)) / 18);
    *Sector = ((LBA % (2 * 18)) % 18 + 1);
}

FOSKERNELAPI
VOID
FDCWait(
    void
)
{
    while(!FDCInterrupt)
        ;;

    FDCInterrupt = 0;
}

FOSKERNELAPI
BOOL
FDCIsReady(
    void
)
{
    char ReceivedByte;

    ReceivedByte = inb(FDC_MAIN_STATUS);

    if (ReceivedByte & FDC_MSR_RQM)
        return TRUE;
    else
        return FALSE;
}

FOSKERNELAPI
BOOL
FDCWaitUntilReady(
    void
)
{
    BOOL Status;
    int Count;

    for (Count = 0; Count < 2000; Count++)
    {
        Status = FDCIsReady();

        if (Status)
        {
            return Status;
        }
    }

    BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "FDC: Not ready");
}

FOSKERNELAPI
FOSSTATUS
FDCSeekTrackSide(
    UCHAR Track,
    UCHAR Side
)
{
    char ReceivedByte;
    int Counter = 0;

    while (1)
    {
        FDCSendByte(FDC_SEEK);
        FDCSendByte(Side * 4);
        FDCSendByte(Track);
        FDCSendByte(FDC_SENSE_INTERRUPT);

        // FDCWait();

        if (!FDCIsReady())
        {
            BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "FDC: Failed to seek (Drive not ready)\n");
        }

        ReceivedByte = FDCReceiveByte();

        if (ReceivedByte == (CHAR)Track)
            return STATUS_SUCCESS;

        if (Counter >= 5000)
        {
            BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "FDC: Failed to seek (Track not found)\n");
        }

        Counter++;
    }
}

FOSKERNELAPI
FOSSTATUS
FDCSeek(
    int Base,
    UINT Cylinder,
    int Head
)
{
    UINT i, St0, Cyl = -1;

    FDCMotorON(Base);

    for (i = 0; i < 10; i++)
    {
        FDCSendByte(FDC_SEEK);
        FDCSendByte(Head << 2);
        FDCSendByte(Cylinder);

        FDCWait();

        FDCSendByte(FDC_SENSE_INTERRUPT);

        St0 = FDCReceiveByte();
        Cyl = FDCReceiveByte();

        if (St0 & 0xC0)
        {
            static const PCHAR status[] = {"Normal", "Error", "Invalid", "Drive"};
            kprintf("FDC: Floppy seek status %s\n", status[St0 >> 6]);
            continue;
        }

        if (Cyl == Cylinder)
        {
            FDCMotorOFF(Base);
            return STATUS_SUCCESS;
        }
    }

    BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION ,"FDC: Failed to seek\n");
    
    return STATUS_UNSUCCESSFUL;
}

FOSKERNELAPI
FOSSTATUS
FDCDoTrack(
    int Base,
    unsigned Cylinder,
    FDCDirection Direction
)
{
    UCHAR Command;
    static const int Flags = 0xc0;

    switch(Direction)
    {
        case FDC_Dir_Read:
            Command = FDC_READ_DATA | Flags;
            FDCPrepareDMARead();
            break;
        case FDC_Dir_Write:
            Command = FDC_WRITE_DATA | Flags;
            FDCPrepareDMAWrite();
            break;
        default:
            kprintf("FDC: invalid direction\n");
            return 0;
    }

    if (FDCSeek(Base, Cylinder, 0) != STATUS_SUCCESS) return STATUS_UNSUCCESSFUL;
    if (FDCSeek(Base, Cylinder, 1) != STATUS_SUCCESS) return STATUS_UNSUCCESSFUL;

    for (int i = 0; i < 20; i++)
    {
        FDCMotorON(Base);

        FDCInitDMA(Direction);

        wait(15);

        FDCSendByte(Command);
        FDCSendByte(0);
        FDCSendByte(Cylinder);
        FDCSendByte(0);
        FDCSendByte(1);
        FDCSendByte(2);
        FDCSendByte(18);
        FDCSendByte(0x1b);
        FDCSendByte(0xff);

        FDCWait();

        UCHAR St0, St1, St2, Rcy, Rhe, Rse, Bps;

        St0 = FDCReceiveByte();
        St1 = FDCReceiveByte();
        St2 = FDCReceiveByte();
        Rcy = FDCReceiveByte();
        Rhe = FDCReceiveByte();
        Rse = FDCReceiveByte();
        Bps = FDCReceiveByte();

        int Error = 0;

        if (St0 & 0xc0)
        {
            static const PCHAR Status[] = {0, "Error", "Invalid command", "Drive not ready"};
            kprintf("FDC: status %s\n", Status[St0 >> 6]);
            Error = 1;
        }

        if (St1 & 0x80)
        {
            kprintf("FDC: End of cylinder\n");
            Error = 1;
        }

        if (St1 & 0x20)
        {
            kprintf("FDC: CRC Error\n");
            Error = 1;
        }

        if (St1 & 0x10)
        {
            kprintf("FDC: Controller timeout\n");
            Error = 1;
        }

        if (St1 & 0x04)
        {
            kprintf("FDC: No data found\n");
            Error = 1;
        }

        if ((St1 | St2) & 0x01)
        {
            kprintf("FDC: No address mark\n");
            Error = 1;
        }

        if (St2 & 0x40)
        {
            kprintf("FDC: Deleted address mark\n");
            Error = 1;
        }

        if (St2 & 0x20)
        {
            kprintf("FDC: CRC Error in data\n");
            Error = 1;
        }

        if (St2 & 0x10)
        {
            kprintf("FDC: Wrong cylinder\n");
            Error = 1;
        }

        if (St2 & 0x04)
        {
            kprintf("FDC: Sector not found\n");
            Error = 1;
        }

        if (St2 & 0x02)
        {
            kprintf("FDC: Bad cylinder\n");
            Error = 1;
        }

        if (Bps != 0x02)
        {
            kprintf("FDC: 512 got %d\n", (1 << (Bps + 7)));
            Error = 1;
        }

        if (St1 & 0x02)
        {
            kprintf("FDC: Not writable\n");
            Error = 2;
        }

        if (!Error)
        {
            FDCMotorOFF(Base);
            return STATUS_UNSUCCESSFUL;
        }

        if (Error > 1)
        {
            kprintf("FDC: Failed\n");
            FDCMotorOFF(Base);
            return STATUS_SUCCESS;
        }
    }

    kprintf("FDC: Too many retries\n");
    FDCMotorOFF(Base);

    return STATUS_UNSUCCESSFUL;
}

FOSKERNELAPI
CHAR
FDCGetDMAByte(
    long Bytes
)
{
    return FDCDMABUFF[Bytes];
}

FOSKERNELAPI
FOSSTATUS
FDCSendByte(
    char Byte
)
{
    int Count = 0;

    while (1)
    {
        if (FDCWaitUntilReady())
        {
            outb(FDC_DATA_FIFO, Byte);

            return STATUS_SUCCESS;
        }

        if (Count >= 1000)
        {
            BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "FDC: Failed to send byte");
        }

        Count++;
    }
}

FOSKERNELAPI
INT
FDCReceiveByte(
    void
)
{
    int Count = 0;

    while (1)
    {
        if (FDCWaitUntilReady())
        {
            return inb(FDC_DATA_FIFO);
        }

        if (Count >= 1000)
        {
            BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "FDC: Failed to receive byte");
        }

        Count++;
    }

}

FOSKERNELAPI
VOID
FDCRecalibrate(
    int DriveType
)
{
    char ReceivedByte;
    int Counter = 0;

    FDCMotorON(DriveType);

    wait(10);

    while (1)
    {
        FDCSendByte(FDC_RECALIBRATE);
        FDCSendByte(0);
        FDCSendByte(FDC_SENSE_INTERRUPT);

        if (!FDCIsReady())
            continue;

        ReceivedByte = FDCReceiveByte();

        if (ReceivedByte)
        {
            break;
        }

        if (Counter >= 1000)
        {
            BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "FDC: Failed to recalibrate");
        }

        Counter++;
    }

    FDCMotorOFF(DriveType);

    kprintf("FDC: Recalibrated\n");
}

FOSKERNELAPI
VOID
FDCMotorON(
    int DriveType
)
{
    outb(FDC_DIGITAL_OUT, FDC_DOR_MOT_A_ON);
    wait(15);
    // kprintf("FDC: Motor ON\n");
}

FOSKERNELAPI
VOID
FDCMotorOFF(
    int DriveType
)
{
    outb(FDC_DIGITAL_OUT, FDC_DOR_MOT_A_OFF);
    wait(15);
    // kprintf("FDC: Motor OFF\n");
}

FOSKERNELAPI
FOSSTATUS
FDCReset(
    int DriveType
)
{
    char Drives[] = {0x1c, 0x3d, 0x4e, 0x8f};
    int DORBackUp = 0;

    DORBackUp = inb(FDC_DIGITAL_OUT);

    outb(FDC_DIGITAL_OUT, FDC_DOR_RESET);
    outb(FDC_DIGITAL_OUT, DORBackUp);

    // FDCWait();

    outb(FDC_CONF_CONTROL, 0x00);

    outb(FDC_DIGITAL_OUT, FDC_DOR_MOT_A_OFF);

    kprintf("FDC: Turned off controller\n");

    FDCRecalibrate(DriveType);

    //FDCWait();
    
    return STATUS_SUCCESS;
}

FOSKERNELAPI
VOID
FDCPrepareDMAWrite(
    void
)
{
    DMAMask(2);
    DMASetWorkMode(2, 0b01010100);
    DMAUnMask(2);
}

FOSKERNELAPI
VOID
FDCPrepareDMARead(
    void
)
{
    DMAMask(2);
    DMASetWorkMode(2, 0b01011000);
    DMAUnMask(2);
}

FOSKERNELAPI
VOID
FDCInitDMA(
    FDCDirection Direction
)
{
    // DMAMask(2);
    // DMAResetFlipFlop(2);
    // DMASetBufferAddr2(0x1000);
    // DMAResetFlipFlop(2);
    // DMASetCycles2(0x23ff);
    // DMAUnMask(2);
    union
    {
        UCHAR Bytes[4];
        ULONG Longl;
    } A, C;

    A.Longl = (unsigned)&FDCDMABUFF;
    C.Longl = (unsigned)0x4800 - 1;

    if ((A.Longl >> 24) || (C.Longl >> 16) || (((A.Longl & 0xffff) + C.Longl) >> 16))
    {
        BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "FDC: DMA buffer trouble");
    }

    UCHAR Mode;

    switch(Direction)
    {
        case FDC_Dir_Read:
            Mode = 0x46;
            break;
        case FDC_Dir_Write:
            Mode = 0x4a;
            break;
        default:
            BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "FDC: DMA Invalid direction");
    }

    outb(0x0a, 0x06);

    outb(0x0c, 0xff);
    outb(0x04, A.Bytes[0]);
    outb(0x04, A.Bytes[1]);

    outb(0x81, A.Bytes[2]);

    outb(0x0c, 0xff);
    outb(0x05, C.Bytes[0]);
    outb(0x05, C.Bytes[1]);

    outb(0x0b, Mode);

    outb(0x0a, 0x02);

    kprintf("FDC: DMA initialized\n");
}

FOSKERNELAPI
VOID
FDCInit(
    int DriveType
)
{
    IRQInstall(6, FDCHandler);
    FDCReset(DriveType);

    kprintf("FDC: Initialized\n");
}