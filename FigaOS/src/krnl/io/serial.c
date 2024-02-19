/** @file serial.c
 *  Copyright (c) 2023 FigaSystems
 *  Serial port interface I/O
 *  @author Daniil Dunaef
 *  @date 21-Dec-2023
 *  @bug No current bugs found
*/



#include "FOSdef.h"
#include "FOSstatus.h"
#include "serial/serial.h"
#include "io/io.h"
#include "libs/headers/string.h"

FOSKERNELAPI
FOSSTATUS
SerialInit(
    PSerial SerialPort,
    INT SerialPortNumber
)
{
    FOSSTATUS Status = STATUS_SUCCESS;

    SerialPort->SerialPort = SerialPortNumber;

    outb(SerialPort->SerialPort + 1, 0x00);
    outb(SerialPort->SerialPort + 3, 0x80);
    outb(SerialPort->SerialPort + 0, 0x03);
    outb(SerialPort->SerialPort + 1, 0x00);
    outb(SerialPort->SerialPort + 3, 0x03);
    outb(SerialPort->SerialPort + 2, 0xC7);
    outb(SerialPort->SerialPort + 4, 0x0B);
    outb(SerialPort->SerialPort + 4, 0x1E);
    outb(SerialPort->SerialPort + 0, 0xAE);

    if (inb(SerialPort->SerialPort + 0) != 0xAE)
    {
        Status = STATUS_UNSUCCESSFUL;

        return Status;
    }
    else
    {
        outb(SerialPort->SerialPort + 4, 0x0F);

        return Status;
    }
}

FOSKERNELAPI
INT
SerialReceived(
    PSerial SerialPort
)
{
    return inb(SerialPort->SerialPort + 5) & 1;
}

FOSKERNELAPI
CHAR
SerialRead(
    PSerial SerialPort
)
{
    while (SerialReceived(SerialPort) == 0);

    return inb(SerialPort->SerialPort);
}

FOSKERNELAPI
INT
SerialIsEmpty(
    PSerial SerialPort
)
{
    return inb(SerialPort->SerialPort + 5) & 0x20;
}

FOSKERNELAPI
VOID
SerialWrite(
    PSerial SerialPort,
    PCHAR SerialData
)
{
    while (SerialIsEmpty(SerialPort) == 0)
        ;

    SerialPort->SerialData = SerialData;

    SerialPort->SerialDataLength = strlen(SerialData);

    for (int i = 0; i < SerialPort->SerialDataLength; i++)
    {
        outb(SerialPort->SerialPort, SerialPort->SerialData[i]);
    }
}

FOSKERNELAPI
VOID
SerialDirectWrite(
    INT SerialPort,
    PCHAR SerialData
)
{
    while (SerialIsEmpty(SerialPort) == 0)
        ;

    for (int i = 0; i < strlen(SerialData); i++)
    {
        outb(SerialPort, SerialData[i]);
    }
}