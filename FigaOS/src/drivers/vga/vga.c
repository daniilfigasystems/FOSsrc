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

unsigned short * vmem = (unsigned short *)VIDEO_ADDRESS;

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
	
	unsigned int i=0;
	for (int y; y < 80; y++)
	{
		for (int x; x < 25; x++)
			VGAPutEntry(' ', x, y, 0x00);
    }
}

void
VGAPutEntry(
	char entry,
	int color,
    int x,
    int y
)
{
	unsigned short *where;
	unsigned att = color << 8;
	where = vmem + (x * 80 + y);
	*where = entry | att;
}

void 
VGAPrintString(
	char *str, 
	int color,
    int x,
    int y
)
{

	while(*str != 0) 
	{
        VGAPutEntry(*str, color, x, y);
        x++;
		// VGAPutEntry(*str, colorbg, colorfg);
		// str++;
	}
}