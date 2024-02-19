/** @file serial.h
 *  Copyright (c) 2023 FigaSystems
 *  Serial port interface I/O
 *  @author Daniil Dunaef
 *  @date 21-Dec-2023
 *  @bug No current bugs found
*/



#ifndef _SERIAL_
#define _SERIAL_

#include "FOSdef.h"
#include "FOSstatus.h"

#define COM1 0x3f8 // COM1

typedef struct _Serial
{
    PCHAR SerialData;
    INT SerialPort;
    USHORT SerialPortBaudRate;
    INT SerialDataLength;
} Serial;

typedef Serial *PSerial;

FOSKERNELAPI
FOSSTATUS
SerialInit(
    PSerial SerialPort,
    INT SerialPortNumber
);

FOSKERNELAPI
INT
SerialReceived(
    PSerial SerialPort
);

FOSKERNELAPI
CHAR
SerialRead(
    PSerial SerialPort
);

FOSKERNELAPI
INT
SerialIsEmpty(
    PSerial SerialPort
);

FOSKERNELAPI
VOID
SerialWrite(
    PSerial SerialPort,
    PCHAR SerialData
);

FOSKERNELAPI
VOID 
SerialDirectWrite(
    INT SerialPort,
    PCHAR SerialData
);

#endif /* !_SERIAL_! */