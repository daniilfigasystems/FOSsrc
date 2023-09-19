

int k_main() {
int e = "d";
kcls(0x17); 
kprintf("ski", 1, 0x07, 1);
kprintf("dedlication", 1, 0x07, 1);
kprintf("uzbekistance", 1, 0x07, 1);
idt_install();
isrs_install();
irq_install();
gdt_install();
kcls(0x07);
vesa_init();
kprintf("test", 1, 0x07, 1);
}