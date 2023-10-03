extern int cr0read();
extern void cr0write();
extern int cr3read();
extern void cr3write();
int kheap = 0x00100000;
#define  mem_min 0x00100001;
#define  mem_max 0x00EFFFFF;
#define  total_mem mem_max - mem_min;
unsigned long *paged = (unsigned long *) 0x9C000;
unsigned long *paget = (unsigned long *) 0x9D000;
typedef struct {
	unsigned char status;
	unsigned int size;
} alloc_t;
void page_init() {
unsigned long address=0; 
unsigned int i;
for(i=0; i<1024; i++)
{
paget[i] = address | 3; 
address = address + 4096; 
}
paged[0] = paget; 
paged[0] = paged[0] | 3;
for(i=1; i<1024; i++)
{
paged[i] = 0 | 2;
}
write_com(" page initializated");
}
void enable_paging() {
cr3write(paged);
cr0write(cr0read() | 0x80000000);
if (cr0read() == 0) {
    write_com(" PAGING FAULT!");
}
else {
    write_com(" PAGING ENABLED!");
}
}
void kfree() {
    int i;
    for (i < mem_max; i++) {
        if (i == 0) {
            write_com(" mem block found!");
            return i;
            break;
        }
        else {
            i = 0;
        }
    }
}
void malloc (alloc_t addr) {
    if (addr.status == 0) {
        write_com(" memory block found");
        addr.size = sizeof(addr);
        write_com(" memory block size is :");
        write_com(addr.size);
        return addr;
    }
   else {
    write_com(" memory block not found");
    return 0;
   }
}