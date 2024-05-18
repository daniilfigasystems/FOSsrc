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
#include "misc/kprintf.h"
#include "timers/pic/pic.h"
#include "irq/irq.h"
#include "io/io.h"

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

FOSSYSAPI
VOID
KeybHandler(
    void
)
{
    int scan;
    register int i;

    scan = inb(0x60);
    i = inb(0x61);
    kprintf("key pressed/released %c\n", kbdus[scan]);
    outb(0x61, i|0x80);
    outb(0x61, i);
    PICSendEOI(1);
}

FOSSYSAPI
FOSSTATUS
KeybInitializeKeyboardPS2(
    void
)
{
    FOSSTATUS status;

    // outb(0x64, 0xAA);
    // outb(0x20, 0xF8);

    // if (inb(0x64) == 0xFC)
    // {
    //     SerialDirectWrite(COM1, "Failed to test keyboard PS2");
    //     status = STATUS_UNSUCCESSFUL;
    //     return status;
    // }

    outb(0x64, 0xAE);

    IRQInstall(1, KeybHandler);
    PICRemap();

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