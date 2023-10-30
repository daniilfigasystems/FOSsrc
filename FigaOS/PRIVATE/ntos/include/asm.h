unsigned char inb(unsigned short port);

void outb(unsigned short port, unsigned char value);
void outw(unsigned short port, unsigned char value);
unsigned char inw(unsigned short port);
void iowait(void);

static inline void cpuid(int code, unsigned int* a, unsigned int* d);

void getch();
void cli(); 
void sti();
void halt(); 

void wait_for_io(unsigned int timer_count);

void suspend(unsigned int timer_count);

