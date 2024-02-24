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
    Serial Com1;

    GDTInstall();

    InbvInitVideoBuffer(addr->framebuffer_addr, addr->framebuffer_pitch, addr->framebuffer_width, addr->framebuffer_height, addr->framebuffer_bpp, addr->framebuffer_type);

    SerialInit(&Com1, COM1);
    SerialWrite(&Com1, "init: Welcome to os");
    InbvFillRect(0, 0, addr->framebuffer_width, addr->framebuffer_height, 0x4444);
    InbvLoadPSFFont();
}

