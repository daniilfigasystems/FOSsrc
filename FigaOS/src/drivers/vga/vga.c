/** @file vga.c
 *  Copyright (c) 2023 FigaSystems
 *  VGA related functions
 *  @author Daniil Dunaef
 *  @date 15-Nov-2023
 *  @bug No current bugs found
*/



#include "vga/vga.h"
#include "misc/kprintf.h"
#include "FOSdef.h"
#include "io/io.h"
#include "libs/headers/stdarg.h"

unsigned short * vmem = (unsigned short *)VIDEO_ADDRESS;
int vcolor;

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
	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 80; x++)
			VGAPutEntry(' ', x, y, vcolor);
    }

	gotoxy(0, 0);
}

void
VGAPutEntry(
	char entry,
    int x,
    int y,
	int color
)
{
	unsigned short *where;
	unsigned att = color << 8;
	where = vmem + (y * 80 + x);
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

void
VGASetColor(
	int color
)
{
	vcolor = color;
}

int
VGAGetColor(
	void
)
{
	return vcolor;
}

void
VGASetVideoMode(
	void
)
{
	outb(0x3C0, 0x10);
	outb(0x3C0, 0x01);
	outb(0x3C0, 0x11);
	outb(0x3C0, 0x00);
	outb(0x3C0, 0x12);
	outb(0x3C0, 0x0F);
	outb(0x3C0, 0x13);
	outb(0x3C0, 0x00);
	outb(0x3C0, 0x14);
	outb(0x3C0, 0x00);
	outb(0x3C2, 0xE3);
	outb(0x3C4, 0x01);
	outb(0x3C4, 0x01);
	outb(0x3C4, 0x03);
	outb(0x3C4, 0x00);
	outb(0x3C4, 0x04);
	outb(0x3C4, 0x02);
	outb(0x3CE, 0x05);
	outb(0x3CE, 0x00);
	outb(0x3CE, 0x06);
	outb(0x3CE, 0x05);
	outb(0x3D4, 0x00);
	outb(0x3D4, 0x5F);
	outb(0x3D4, 0x01);
	outb(0x3D4, 0x4F);
	outb(0x3D4, 0x02);
	outb(0x3D4, 0x50);
	outb(0x3D4, 0x03);
	outb(0x3D4, 0x82);
	outb(0x3D4, 0x04);
	outb(0x3D4, 0x54);
	outb(0x3D4, 0x05);
	outb(0x3D4, 0x80);
	outb(0x3D4, 0x06);
	outb(0x3D4, 0x0B);
	outb(0x3D4, 0x07);
	outb(0x3D4, 0x3E);
	outb(0x3D4, 0x08);
	outb(0x3D4, 0x00);
	outb(0x3D4, 0x09);
	outb(0x3D4, 0x40);
	outb(0x3D4, 0x10);
	outb(0x3D4, 0xEA);
	outb(0x3D4, 0x11);
	outb(0x3D4, 0x8C);
	outb(0x3D4, 0x12);
	outb(0x3D4, 0xDF);
	outb(0x3D4, 0x13);
	outb(0x3D4, 0x28);
	outb(0x3D4, 0x14);
	outb(0x3D4, 0x00);
	outb(0x3D4, 0x15);
	outb(0x3D4, 0xE7);
	outb(0x3D4, 0x16);
	outb(0x3D4, 0x04);
	outb(0x3D4, 0x17);
	outb(0x3D4, 0xE3);

}