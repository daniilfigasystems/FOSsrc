#include "stdarg.h"
typedef struct regs
{
    unsigned int gs, fs, es, ds;      
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  
    unsigned int int_no, err_code;    
    unsigned int eip, cs, eflags, useresp, ss;   
    unsigned int ax, dx, cx;
    unsigned int bl, bh;
    unsigned int di; 
};
char* vmem;
int row, col;
int color;
void kcls(int clr) 
{
	vmem = (char *)0xb8000;
	unsigned int i=0;
	write_com(0x3f8, " cleared screen ");
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
void kprintf(char *string, unsigned int line, unsigned int color, char x1) 
{
	char *vmem = (char *) 0xb8000;
	unsigned int i=0;
	int y = get_y_cur();
    int x = get_x_cur();
	i=(y*x*2);
			write_com(0x3f8, " printed string: ");
			write_com(0x3f8, string);
			write_com(0x3f8, " ");
	while(*string != 0) {
		if (*string == '\n') 
		{
			line++;
			i=(line*x*2);
			*string++;
			update_cur(x, y+1);
		}
		else 
		{
			vmem[i]=*string;
			*string++;
			i++;
			vmem[i]=color;
			i++;
			update_cur(x+1,y+1);
		}
	}
}
