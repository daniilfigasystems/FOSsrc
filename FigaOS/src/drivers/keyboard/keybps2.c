/** @file io.h
 *  Copyright (c) 2023 FigaSystems
 *  Inport and outport functions
 *  @author Daniil Dunaef
 *  @date 1-Dec-2023
 *  @bug No current bugs found
 */

#include "keyboard/keybps2.h"
#include "FOSdef.h"
#include "FOSstatus.h"
#include "serial/serial.h"
#include "io/io.h"

FOSSYSAPI
FOSSTATUS
KeybInitializeKeyboardPS2(
    void
)
{
    FOSSTATUS status;

    outb(0x64, 0xAA);

    if (inb(0x64) == 0xFC)
    {
        SerialDirectWrite(COM1, "Failed to test keyboard PS2");
        status = STATUS_UNSUCCESSFUL;
        return status;
    }

    outb(0x64, 0xAE);

    status = STATUS_SUCCESS;
    return status;
}

FOSSYSAPI
VOID 
KeybTurnOnLED(
    KeybLedState LEDNum
)
{
    outb(0x60, 0xED);
    outb(0x60, LEDNum);
}