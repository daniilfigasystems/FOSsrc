/** @file init.c
 *  Copyright (c) 2023 FigaSystems
 *  Initialization
 *  @author Daniil Dunaef
 *  @date 15-Nov-2023
 *  @bug No current bugs found
 */

#include "multiboot.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "vga/vga.h"
#include "mm/mm.h"
#include "vesa/vesa.h"
#include "libs/headers/string.h"
#include "FOSdef.h"
#include "CMOS/cmos.h"
#include "io/io.h"
#include "serial/serial.h"
#include "check/bugcheck.h"
#include "FOSstatus.h"

FOSSTATUS Status;

int KernelEntry(unsigned long magic, MULTIBOOT_INFO *addr)
{
    LONG MemorySize;
    DriveType DT1, DT2;
    VideoFrameBufferAddress vaddr = (ULONG)addr->framebuffer_addr;
    UINT vpitch = addr->framebuffer_pitch, vwidth = addr->framebuffer_width, vheight = addr->framebuffer_height;
    UCHAR vbpp = addr->framebuffer_bpp, vtype = addr->framebuffer_type;

    GDTInstall();

    InbvInitVideoBuffer(vaddr, vpitch, vwidth, vheight, vbpp, vtype);

    SerialDirectWrite(COM1, "init: Welcome to os");
    InbvLoadPSFFont();
    InbvDrawCharacter('c', 190, 10, 0x55555555, 0xddd);
    InbvFillRect(10, 40, 300, 200, 0x55555555);
}

