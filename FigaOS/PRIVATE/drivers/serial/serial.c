
#define COM1 0x3f8
void int_com() {
outb(COM1+1, 0x00);
outb(COM1+3, 0x80);
outb(COM1+0, 0x03);
outb(COM1+1, 0x00);
outb(COM1+3, 0x03);
outb(COM1+2, 0xC7);
outb(COM1+4, 0x0B);
outb(COM1+4, 0x1E);
outb(COM1+0, 0xAE);
if (inb(COM1+0) != 0xAE) {
    kprintf("serial port fault", 1, 0x07, 1);
    return 1;
}
outb(COM1+4, 0x0F);
return 0;
}
int com_receive() {
    return inb(COM1+5) & 1;
}
char read_com() {
    while (com_receive() == 0) {
        return inb(COM1);
    }
}
int ite() {
    return inb(COM1+5) & 0x20;
    return inb(COM1);
}
void write_com(char *data) {
    while (ite() == 0);
    int i;
    for (i = 0; i < strlen(data); i++) {
    outb(COM1, data[i]);
    }
}