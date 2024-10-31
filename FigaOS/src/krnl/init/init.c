/** @file init.c
 *  Copyright (c) 2023 FigaSystems
 *  Initialization
 *  @author Daniil Dunaef
 *  @date 15-Nov-2023
 *  @bug No current bugs found
 */

#include "multiboot.h"
#include "gdt/gdt.h"
#include "irq/irq.h"
#include "BIOS/bios.h"
#include "idt/idt.h"
#include "vga/vga.h"
#include "keyboard/keybps2.h"
#include "mm/mm.h"
#include "mm/paging.h"
#include "vesa/vesa.h"
#include "libs/headers/string.h"
#include "FOSdef.h"
#include "CMOS/cmos.h"
#include "v86/v86.h"
#include "fdc/fdc.h"
#include "io/io.h"
#include "serial/serial.h"
#include "isr/isr.h"
#include "check/bugcheck.h"
#include "check/bugcodes.h"
#include "misc/kprintf.h"
#include "multithreading/schedule.h"
#include "FOSstatus.h"
#include "regs/regs.h"
#include "timers/pic/pic.h"
#include "timers/pit/pit.h"
#include "debug/debug.h"
#include "BIOS/bios.h"
#include "BIOS/boot.h"

FOSSTATUS Status;

int KernelEntry(unsigned long magic, MULTIBOOT_INFO *addr)
{
    LONG MemorySize;
    DriveType DT1, DT2;

    VGASetColor(0x70);
    VGAInit();
    kprintf("FOSKRNL 386\n");
    GDTInstall();
    // sti();
    IDTInstall();
    PGInitializePaging();
    MemorySize = CMOSGetMemorySize();
    kprintf("%d KB Memory\n", MemorySize);
    if (MemorySize < 8096)
        kprintf("Warning: Using less than 8 MB may be laggy\n");
    if (MemorySize < 3072)
        BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "Not enough memory. System is deadlocked on memory");
    IRQInitialize();
    ISRInitialize();
    MMInitializeMemory(0x100000, MemorySize*1024);
    sti();
    PICRemap();
    PICUnmask(100);
    PITInit(250);
    dump();
    wait(1);
    for (int i = 0; i < 80; i++)
        kprintf("=");
    for (int i = 0; i < 64; i++)
    {
        wait(3);
        kprintf(".");
    }
    kprintf("\n");
    KeybInitializeKeyboardPS2();
    FDCInit(0);
    kprintf("FigaOS Version 0.02DEV\n");
    for (int i = 0; i < 70; i++)
    {
        kprintf(".");
        FDCSeek(0, i, 1);
        FDCSeekTrackSide(i, 1);
        // FDCDoTrack(0, i, FDC_Dir_Read);
    }
    VGAInit();
    wait(1000);
    VGASetVideoMode();
    KeybResetCPU();
    // BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "FDC: Failed to configure driver work propertly sigma kriper\n");
}

