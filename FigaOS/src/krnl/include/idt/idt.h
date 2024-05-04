#include "FOSdef.h"

typedef struct _idt_entry
{
    unsigned short base_low;
    unsigned short sel;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed)) idt_entry;

typedef struct _idtr
{
	unsigned short limit;
	unsigned int* base;
} __attribute__((packed)) idtr;

extern void IDTi();

FOSKERNELAPI
VOID
IDTSetGate(
    unsigned short num,
    unsigned long base,
    unsigned short sel,
    unsigned char flags
);

FOSKERNELAPI
VOID
IDTInstall(
    void
);