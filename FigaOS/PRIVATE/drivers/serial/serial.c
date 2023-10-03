
#define COM1 0x3f8
#define COM2 0x2f8
void int_com1() 
{
outb(COM1+1, 0x00);
outb(COM1+3, 0x80);
outb(COM1+0, 0x03);
outb(COM1+1, 0x00);
outb(COM1+3, 0x03);
outb(COM1+2, 0xC7);
outb(COM1+4, 0x0B);
outb(COM1+4, 0x1E);
outb(COM1+0, 0xAE);
if (inb(COM1+0) != 0xAE) 
{
    kprintf("serial port number 1 fault", 1, 0x07, 1);
    return 1;
}
}
void int_com2() 
{
outb(COM2+1, 0x00);
outb(COM2+3, 0x80);
outb(COM2+0, 0x03);
outb(COM2+1, 0x00);
outb(COM2+3, 0x03);
outb(COM2+2, 0xC7);
outb(COM2+4, 0x0B);
outb(COM2+4, 0x1E);
outb(COM2+0, 0xAE);
if (inb(COM2+0) != 0xAE) 
{
    kprintf("serial port number 2 fault", 1, 0x07, 1);
    return 1;
}
outb(COM2+4, 0x0F);
return 0;
}
int com_receive(int com) 
{
    return inb(com+5) & 1;
}
char read_com(int com) 
{
    while (com_receive(com) == 0) 
    {
        return inb(com);
    }
}
int ite(int com) 
{
    return inb(com+5) & 0x20;
    return inb(com);
}
void write_com(int com, char *data) 
{
    while (ite(com) == 0);
    int i;
    for (i = 0; i < strlen(data); i++) 
    {
    outb(com, data[i]);
    }
}