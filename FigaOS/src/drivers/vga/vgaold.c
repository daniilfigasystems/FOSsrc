/** @file vga.c
 *  Copyright (c) 2023 FigaSystems
 *  VGA related functions
 *  @author Daniil Dunaef
 *  @date 15-Nov-2023
 *  @bug No current bugs found
*/



#include "vga/vga.h"
#include "io/io.h"
#include "libs/headers/stdarg.h"

char* vmem;
int row;
int col;

// void
// VGA_set_cursor_pos(
// 	int x,
// 	int y
// 	)
// {
// 	unsigned short cursorLocation = y * 80 + x;
//     outb(0x3D4, 14);
//     outb(0x3D5, cursorLocation >> 8);
//     outb(0x3D4, 15);
//     outb(0x3D5, cursorLocation);
// }

// void
// VGA_get_cursor_pos(
// 	void
// 	)
// {
// 	unsigned short pos = 0;
//     outb(0x3D4, 0x0F);
//     pos |= inb(0x3D5);
//     outb(0x3D4, 0x0E);
//     pos |= ((unsigned short)inb(0x3D5)) << 8;
//     return pos;
// }

unsigned 
short 
VGAItemEntry(
	unsigned char ch, 
	VGA_COLOR_TYPE fore_color, 
	VGA_COLOR_TYPE back_color
) 
{
    unsigned short ax = 0;
    unsigned char ah = 0, al = 0;

    ah = back_color;
    ah <<= 4;
    ah |= fore_color;
    ax = ah;
    ax <<= 8;
    al = ch;
    ax |= al;

    return ax;
}

void
VGAInit(
    void
)
{
	vmem = (char *)VIDEO_ADDRESS;
	unsigned int i=0;
	while (i < (80*25*2)) 
	{
		vmem[i] = ' ';
		i++;
		vmem[i] = 0x17;
		i++;
    }
}

void
VGAPutEntry(
	char entry,
	char color
)
{
	char *vmem = (char *) VIDEO_ADDRESS;
	unsigned int i=0;
	i=(row*col*2);
	if (entry == '\n') 
	{
	}
	else
	{
		// vmem[i++] = VGAItemEntry(entry, colorbg, colorfg);
		// vmem[i] = *entry;
		// col++;
		vmem[i] = entry;
		i++;
		vmem[i] = color;
		i++;
		col++;
	}
}

void 
VGAPrintString(
	char *str, 
	int color
)
{
	unsigned int i=0;
	i=(row*col*2);

	while(*str != 0) 
	{
		vmem[i]= *str;
		*str++;
		i++;
		vmem[i] = color;
		i++;
		col++;
		// VGAPutEntry(*str, colorbg, colorfg);
		// str++;
	}
}

void
VGANewLine(
	void
)
{
	row++;
	col = 0;
	col += 80;
}