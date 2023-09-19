unsigned char inb(unsigned short port);


void outb(unsigned short port, unsigned char value);


void iowait(void);

static inline void cpuid(int code, unsigned int* a, unsigned int* d)
{
    asm volatile ( "cpuid" : "=a"(*a), "=d"(*d) : "0"(code) : "ebx", "ecx" );
void getch() {
  int sc=0;
  asm volatile ( "xor ah, ah\n\t" 
  "int 16h\n\t" 
  "ret\n\t");
  return sc;
}
}

