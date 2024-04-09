#include "idt/idt.h"
#include "libs/headers/string.h"
#include "FOSdef.h"

idt_entry idt[256];
idtr idtptr;

FOSKERNELAPI
VOID
IDTSetGate(
    unsigned short num,
    unsigned short base,
    unsigned short sel,
    unsigned char flags
)
{
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].base_low = (base & 0xFFFF);
    idt[num].zero = 0;
    idt[num].sel = sel;
    idt[num].flags = flags;
}

FOSKERNELAPI
VOID
IDTInstall(
    void
)
{
    idtptr.limit = (sizeof(idt_entry) * 256) - 1;
    idtptr.base = (PUINT)&idt;
    memset((unsigned char*)&idt, 0, sizeof(idt_entry) * 256);
    IDTi();
}