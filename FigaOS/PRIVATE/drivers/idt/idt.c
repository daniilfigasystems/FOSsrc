
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        
    unsigned char always0;     
    unsigned char flags;       
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));


struct idt_entry idt[256];
struct idt_ptr idtp;



void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 8) & 0xFF;
    idt[num].flags = flags;
    idt[num].sel = sel;
    
}

void idt_install()
{
    
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = &idt;

    
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    
extern void idt_load();
    
    idt_load();
    write_com("idt initializated");
}		