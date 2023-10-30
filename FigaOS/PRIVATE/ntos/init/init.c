#include "stddef.h"
#include "vga.h"
#include "irq.h"
#include "isr.h"
#include "gdt.h"
#include "idt.h"
#include "fpu.h"
#include "page.h"
#include "sb16.h"
#include "malloc.h"
#include "pic.h"
#include "asm.h"
int k_main() {  
char a = "b"; 
enable_a20_line();
NMI_enable();
idt_install();
isrs_install();
irq_install();
gdt_install();
page_init();
enable_paging();
checkfpu();
pic_remap(10, 1);
kcls(0x17); 
kprintf("FigaSystems FigaOS 2021-2023\n", 0x17);
kprintf("NT", 0x17);
reset_DSP();
dbgprint("hi %s", a);
}