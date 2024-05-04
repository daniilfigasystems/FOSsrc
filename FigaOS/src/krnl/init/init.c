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
#include "vesa/vesa.h"
#include "libs/headers/string.h"
#include "FOSdef.h"
#include "CMOS/cmos.h"
#include "io/io.h"
#include "serial/serial.h"
#include "check/bugcheck.h"
#include "misc/kprintf.h"
#include "multithreading/schedule.h"
#include "FOSstatus.h"
#include "regs/regs.h"
#include "timers/pic/pic.h"
#include "timers/pit/pit.h"
#include "BIOS/bios.h"
#include "BIOS/boot.h"

FOSSTATUS Status;

void lol()
{
    kprintf("LOL");
}

int KernelEntry(unsigned long magic, MULTIBOOT_INFO *addr)
{
    LONG MemorySize;
    DriveType DT1, DT2;

    kprintf("INIT: FigaOS 0.02\n");
    GDTInstall();
    IDTInstall();
    MemorySize = CMOSGetMemorySize();
    IRQInitialize();
    MMInitializeMemory(0x1000, MemorySize);
    KeybInitializeKeyboardPS2();
    kprintf("Memory %dKB\n", MemorySize);
    dump();
    kprintf("EAX: %d EBX: %d EBP: %d\n EIP: %d\n", getregs().eax, getregs().ebx, getregs().ebp, getregs().eip);
    PICRemap();
    PICUnmask(100);
    PITInit(100);
    //sti();
    kprintf("free mem: %d\n", MMGetFreeMem());
    wait(10);
    kprintf("hi");
    
}

