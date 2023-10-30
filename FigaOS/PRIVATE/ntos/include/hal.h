void hal_init();

void send_eoi(unsigned char irq);


void set_int(int i, unsigned int addr);

unsigned char inb(unsigned short portid);

unsigned short inw(unsigned short portid);

unsigned int inl(unsigned short portid);

void outb(unsigned short portid, unsigned char value);

void outw(unsigned short portid, unsigned short value);

void outl(unsigned short portid, unsigned int value);

void iowait(void);
