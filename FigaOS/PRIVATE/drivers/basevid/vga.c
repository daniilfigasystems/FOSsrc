#include "stdarg.h"
#include "vga.h"
#include "serial.h"
#include "stdarg.h"
char* vmem;
int row, col, lps;
int color;
void kcls(int clr) 
{
	vmem = (char *)VIDEO_ADDRESS;
	unsigned int i=0;
	write_com(COM1, " cleared screen ");
	while (i < (80*25*2)) {
		vmem[i] = ' ';
		i++;
		vmem[i] = clr;
		i++;
	}
}
unsigned short get_cur_pos(void)
{
    unsigned short pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((unsigned short)inb(0x3D5)) << 8;
    return pos;
}
void enable_cur(int curs, int cure) 
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | curs);
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cure);
}
void disable_cur() 
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}
void update_cur(int x, int y) 
{
	int pos = y*80+x;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (int) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (int) ((pos >> 8) & 0xFF));
}
int get_x_cur() 
{
	int pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((int)inb(0x3D5)) << 8;
	int x;
	x = pos % 80;
	return x;
}
int get_y_cur() 
{
	int pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((int)inb(0x3D5)) << 8;
	int y;
	y = pos / 80;
	return y;
}

void kprintf(char *string, unsigned int color) 
{
	char *vmem = (char *) VIDEO_ADDRESS;
	unsigned int i=0;
	i=(row*col*2);
			write_com(COM1, " printed string: ");
			write_com(COM1, string);
			write_com(COM1, " ");
	while(*string != 0) {
		if (*string == '\n') 
		{
			row++;
			col = 0;
			col += 80;
			i=(row*col*2);
			*string++;
			
		}
		else 
		{
			vmem[i]=*string;
			*string++;
			i++;
			vmem[i]=color;
			i++;
			col++;
		}
	}
}
void dbgprint(char *str, ...) {
	char **arg = (char **)&str;
	int c;
	arg++;
	while ((c = *str++) != 0) {
		if (c != '%') {
			kprintf(*str, 0x17);
		}
		else {
			char *p;
			c = *str++;
			switch(c) {
				case 's':
				p = *arg++;
				if (!p) {
					p = "(0)";
				}
				break;
			}
		}
	}
}