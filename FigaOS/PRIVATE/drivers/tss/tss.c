#include "gdt.h"
#include "tss.h"
#include "string.h"
extern void flush_tss();
struct tss_entry tss_entry32;
 
void write_tss(struct gdt_entry *g) 
{
	
	unsigned int base = (unsigned int) &tss_entry32;
	unsigned int limit = sizeof tss_entry32;
 
	
	g->limit_low = limit;
	g->base_low = base;
	g->access = 1;
	g->read_write = 0;
	g->conforming_expand_down = 0; 
	g->code = 1; 
	g->code_data_segment=0; 
	g->DPL = 0; 
	g->present = 1;
	g->limit_high = (limit & (0xf << 16)) >> 16; 
	g->available = 0; 
	g->long_mode = 0;
	g->big = 0; 
	g->granularity = 0; 
	g->base_high = (base & (0xff << 24)) >> 24; 
 
	memset(&tss_entry32, 0, sizeof tss_entry32);
 
	tss_entry32.ss0  = 0x100000;  
	tss_entry32.esp0 = 0x105000; 
	
}
 
void set_kernel_stack(unsigned int stack) 
{ 
	tss_entry32.esp0 = stack;
}