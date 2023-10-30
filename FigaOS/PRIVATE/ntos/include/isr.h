extern void isr0();
extern void isr1();
extern void isr2();
extern void isr8();
extern void isr14();
extern void isr30();
void isrs_install();
void fault_handler(struct regs *r);