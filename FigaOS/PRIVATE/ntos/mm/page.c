#include "page.h"
unsigned long *paged = (unsigned long *) 0x9C000;
unsigned long *paget = (unsigned long *) 0x9D000;
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