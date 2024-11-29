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
#include "sys/syscall.h"
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
    MMInitializeMemory(0x100000, MemorySize*1024);
    kprintf("%d KB Memory   %d KB Free\n", MemorySize, MMGetFreeMem()/1024);
    if (MemorySize < 8096)
        kprintf("Warning: Using less than 8 MB may be laggy\n");
    if (MemorySize < 1760)
        BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "Not enough memory\n");
    for (int i = 0; i < 80; i++)
        kprintf("=");
    dump();
    IRQInitialize();
    kprintf(".");
    ISRInitialize();
    kprintf(".");
    sti();
    PICRemap();
    kprintf(".");
    PICUnmask(100);
    kprintf(".");
    PITInit(250);
    kprintf(".");
    KeybInitializeKeyboardPS2();
    kprintf(".");
    FDCInit(0);
    kprintf(".");
    SCInit();
    kprintf(".");
    const char* str = "hii";
    regs registers;
    registers.eax = SYSWRITE;
    registers.edi = 1;
    registers.ecx = strlen(str);
    registers.esi = *str;
    // SCSyscall(&registers);
    SCSyscall(&registers);
    kprintf(".");
    // BCPanic(FATAL_UNHANDLED_KERNEL_EXPECTION, "FDC: Failed to configure driver work propertly sigma kriper\n");
}

